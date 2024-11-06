#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "utils.h"

int main(int argc, char *argv){
    int sd, err, nread;
    uint8_t buffer[4096];
    char input[4096];
	struct addrinfo hints, *res, *ptr;

    if(argc!=3){
        fputs("Errore argomenti!",stderr);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

    err = getaddrinfo(argv[1], argv[2], &hints, &res);
	if (err != 0) {
		fprintf(stderr, "Errore gai: %s\n", gai_strerror(err));
		exit(EXIT_FAILURE);
	}

    for (ptr = res; ptr != NULL; ptr = ptr->ai_next) {
		sd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (sd < 0) continue;

		err = connect(sd, ptr->ai_addr, ptr->ai_addrlen);
		if (err == 0) break;

		close(sd);
	}

	if (ptr == NULL) {
		fputs("Errore connessione!", stderr);
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(res);

    while(1){
        printf("Inserisci una stringa (o 'fine' per terminare): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fputs("Errore lettura input!\n", stderr);
            break;
    }

    // Rimuovi il carattere newline dall'input
    input[strcspn(input, "\n")] = 0;
    // Termina se l'input è "fine"
    if (strcmp(input, "fine") == 0) break;
    // Invia stringa al server
    err = write_all(sd, input, strlen(input));
	if (err < 0) {
		fputs("Errore write!", stderr);
		exit(EXIT_FAILURE);
	}
    // Invia newline per indicare la fine della stringa
	err = write(sd, "\n", 1);
	if (err < 0) {
		fputs("Errore write!", stderr);
		exit(EXIT_FAILURE);
	}
    // Leggi risposta dal server (numero di caratteri)
	nread = read(sd, buffer, sizeof(buffer) - 1 ); 
		
	if (nread < 0) {
		fputs("Errore read!", stderr);
		exit(EXIT_FAILURE);
	}
    buffer[nread] = '\0';
    printf("Numero di caratteri: %s\n", buffer);
    }
    close(sd);
	return 0;
}