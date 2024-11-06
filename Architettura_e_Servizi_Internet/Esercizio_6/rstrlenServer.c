#include <stdint.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "rxb.h" // Assumendo che `rxb.h` contenga la funzione `readline` o simile

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    int sd, client_sd, err;
    struct addrinfo hints, *res;
    struct sockaddr_storage client_addr;
    socklen_t client_addr_len;
    char buffer[BUFFER_SIZE];
    char client_host[NI_MAXHOST], client_service[NI_MAXSERV];

    if (argc != 2) {
        fprintf(stderr, "Usage:\n\t%s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    signal(SIGPIPE, SIG_IGN);  // Ignora SIGPIPE per evitare crash in caso di errori di scrittura sul socket

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;       // IPv4 o IPv6
    hints.ai_socktype = SOCK_STREAM;   // TCP
    hints.ai_flags = AI_PASSIVE;       // Usa l'indirizzo IP locale

    err = getaddrinfo(NULL, argv[1], &hints, &res);
    if (err != 0) {
        fprintf(stderr, "Errore getaddrinfo: %s\n", gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    // Creazione del socket
    sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sd < 0) {
        perror("Errore creazione socket");
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    // Associa il socket alla porta specificata
    err = bind(sd, res->ai_addr, res->ai_addrlen);
    if (err < 0) {
        perror("Errore bind");
        close(sd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(res);

    // Inizia ad ascoltare per le connessioni
    err = listen(sd, SOMAXCONN);
    if (err < 0) {
        perror("Errore listen");
        close(sd);
        exit(EXIT_FAILURE);
    }

    printf("Server in ascolto sulla porta %s...\n", argv[1]);

    while (1) {
        client_addr_len = sizeof(client_addr);
        client_sd = accept(sd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sd < 0) {
            perror("Errore accept");
            continue;
        }

        // Ottieni informazioni sul client connesso
        err = getnameinfo((struct sockaddr *)&client_addr, client_addr_len,
                          client_host, NI_MAXHOST, client_service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        if (err == 0) {
            printf("Connessione accettata da %s:%s\n", client_host, client_service);
        } else {
            fprintf(stderr, "Errore getnameinfo: %s\n", gai_strerror(err));
        }

        // Leggi la stringa inviata dal client
        ssize_t nread = readline(client_sd, buffer, BUFFER_SIZE);
        if (nread > 0) {
            buffer[nread] = '\0';  // Aggiunge il terminatore di stringa
            printf("Stringa ricevuta: %s\n", buffer);

            // Conta i caratteri della stringa ricevuta
            int count = strlen(buffer);

            // Prepara e invia la risposta
            snprintf(buffer, sizeof(buffer), "%d\n", count);
            if (write(client_sd, buffer, strlen(buffer)) < 0) {
                perror("Errore invio risposta");
            }
        } else if (nread == 0) {
            printf("Il client ha chiuso la connessione\n");
        } else {
            perror("Errore lettura dal client");
        }

        close(client_sd);  // Chiudi la connessione con il client
    }

    close(sd);  // Chiudi il socket del server
    return 0;
}
  