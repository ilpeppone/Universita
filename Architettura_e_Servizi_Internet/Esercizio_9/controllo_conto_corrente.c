#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define DIM 4096

int main(int argc, char **argv)
{
    int sd, err, nread;
    struct addrinfo hints, *res, *ptr;
    char buf[DIM], categoria[DIM];
    char *host_remoto, *servizio_remoto;
    if (argc != 3)
    {
        perror("Uso:./controllo_conto_corrente server porta");
        exit(EXIT_FAILURE);
    }

    signal(SIGPIPE, SIG_IGN);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    host_remoto = argv[1];
    servizio_remoto = argv[2];

    if ((err = getaddrinfo(host_remoto, servizio_remoto, &hints, &res)) != 0)
    {
        fprintf(stderr, "Errore risoluzione nome: %s\n", gai_strerror(err));
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        printf("Inserisci la categoria da ricercare:\n");
        if (scanf("%s", categoria) == EOF || errno != 0)
        {
            perror("scanf");
            exit(EXIT_FAILURE);
        }
        if (strcmp(categoria, "fine") == 0)
        {
            printf("Hai scelto di terminare il programma\n");
            break;
        }
        for (ptr = res; ptr != NULL; ptr->ai_next)
        {
            sd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
            if (sd < 0)
                continue;
            err = connect(sd, ptr->ai_addr, ptr->ai_addrlen);
            if (err == 0)
                break;
            if (ptr == NULL)
            {
                fputs("Errore connessione", stderr);
                exit(EXIT_FAILURE);
            }
            /* Mando il nome della categoria al server */
            if (write(sd, categoria, strlen(categoria)) < 0)
            {
                perror("write categoria");
                exit(EXIT_FAILURE);
            }
            fflush(stdout);
            while ((nread = read(sd, buf, DIM)) > 0)
            {
                if (write(1, buf, nread) < 0)
                {
                    perror("write su stdout");
                    exit(EXIT_FAILURE);
                }
            }
            if (nread < 0)
            {
                perror("read del risultato");
                exit(EXIT_FAILURE);
            }

            close(sd);
        }
    }
    freeaddrinfo(res);
}