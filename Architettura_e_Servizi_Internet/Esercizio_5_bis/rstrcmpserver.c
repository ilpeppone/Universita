#define _POSIX_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#define MAX_REQUEST_SIZE (64*1024)
#include "utils.h"

void handler(int signo){
    int status;
    (void) signo;
    while(waitpid(-1,&status,WNOHANG)>0)
        continue;
}

int main(int argc,char **argv){
    struct addrinfo hints,*res;
    int sd,err,on;
    struct sigaction sa;

    if (argc!=2){
        fprintf(stderr,"Uso:./rstrlenclient hostname porta\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGPIPE,SIG_IGN);

    sigemptyset(&sa.sa_mask);

    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;

    if(sigaction(SIGCHLD,&sa,NULL)==-1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((err = getaddrinfo(NULL,argv[1],&hints,&res))!=0){
        fprintf(stderr,"Errore setup indirizzo bind %s",gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    if((sd = socket(res->ai_family,res->ai_socktype,res->ai_protocol))<0){
        fprintf(stderr,"Errore socket");
        exit(EXIT_FAILURE);
    }

    on=1;
    if(setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    if(bind(sd,res->ai_addr,res->ai_addrlen)<0){
        perror("Errore in bind");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    /* trasforma in socket passiva d'ascolto */
        if (listen(sd, SOMAXCONN) < 0) {
                perror("listen");
                exit(EXIT_FAILURE);
        }

    for(;;) {
            int ns, pid;

    /* Mi metto in attesa di richieste di connessione */
            if ((ns = accept(sd, NULL, NULL)) < 0) {
                    perror("accept");
                    exit(EXIT_FAILURE);
            }

    /* Creo un processo figlio per gestire la richiesta */
            if ((pid = fork()) < 0) {
                    perror("fork");
                    exit(EXIT_FAILURE);
            } else if (pid == 0) { /* FIGLIO */
        uint8_t len[2];
                    int letti = 0;
                    char stringa1[MAX_REQUEST_SIZE];
        char stringa2[MAX_REQUEST_SIZE];
        size_t dim_stringa1, dim_stringa2, dim_response;
char response[80];

                    /* Chiudo la socket passiva */
                    close(sd);

                    for(;;){ /* Itero fino a che il client non chiude la connessione */
                            /* Leggo lunghezza stringa1 */
                            letti = read_all(ns, len, 2);
                            if (letti < 0) {
                                    perror("read");
                                    exit(EXIT_FAILURE);
                            } else if(letti == 0) {
                                    printf("Client disconnesso.\n");
                                    break;
                            }

                            /* Decodifico lunghezza stringa1 come intero unsigned a
                            * 16 bit in formato big endian (AKA network byte
                            * order) */
                            dim_stringa1 = len[1] | (len[0] << 8);

                            /* Inizializzo il buffer stringa1 a zero e so che
                            * dim_stringa1 < sizeof(stringa1), quindi sono sicuro
                            * che il buffer sarà sempre null-terminated. In questo
                            * modo, posso interpretarlo come una stringa C e
                            * passarlo direttamente alla funzione strcmp. */
                            memset(stringa1, 0, sizeof(stringa1));
                            letti = read_all(ns, stringa1, dim_stringa1);
                            if (letti < 0) {
                                    perror("read");
                                    exit(EXIT_FAILURE);
                            } else if(letti == 0) {
                                    printf("Client disconnesso.\n");
                                    break;
                            }

    #ifdef USE_LIBUNISTRING
            /* Verifico che il messaggio sia UTF-8 valido */
            if (u8_check((uint8_t *)stringa1, dim_stringa1) != NULL) {
                /* Client che malfunziona - inviato messaggio con 
                    * stringa UTF-8 non valida */
                fprintf(stderr, "Request is not valid UTF-8!\n");
                close(ns);
                exit(EXIT_SUCCESS);
            }
    #endif

                            /* Leggo lunghezza stringa2 */
                            letti = read_all(ns, len, 2);
                            if (letti < 0) {
                                    perror("read");
                                    exit(EXIT_FAILURE);
                            } else if(letti == 0) {
                                    printf("Client disconnesso.\n");
                                    break;
                            }

                            /* Decodifico lunghezza stringa2 come intero unsigned a
                            * 16 bit in formato big endian (AKA network byte
                            * order) */
                            dim_stringa2 = len[1] | (len[0] << 8);

                            /* Inizializzo il buffer stringa2 a zero e so che
                            * dim_stringa2 < sizeof(stringa2), quindi sono sicuro
                            * che il buffer sarà sempre null-terminated. In questo
                            * modo, posso interpretarlo come una stringa C e
                            * passarlo direttamente alla funzione strcmp. */
                            memset(stringa2, 0, sizeof(stringa2));
                            letti = read_all(ns, stringa2, dim_stringa2);
                            if (letti < 0) {
                                    perror("read");
                                    exit(EXIT_FAILURE);
                            } else if(letti == 0) {
                                    printf("Client disconnesso.\n");
                                    break;
                            }

    #ifdef USE_LIBUNISTRING
            /* Verifico che il messaggio sia UTF-8 valido */
            if (u8_check((uint8_t *)stringa2, dim_stringa2) != NULL) {
                /* Client che malfunziona - inviato messaggio con 
                    * stringa UTF-8 non valida */
                fprintf(stderr, "Request is not valid UTF-8!\n");
                close(ns);
                exit(EXIT_SUCCESS);
            }
    #endif

                            /* Preparo il buffer contenente la risposta */
                            if (strcmp(stringa1, stringa2) == 0) {
                                    /* Le stringhe sono identiche */
                                    strncpy(response, "SI", sizeof(response));
                            } else {
                                    /* Le stringhe sono diverse */
                                    strncpy(response, "NO", sizeof(response));
                            }

                            /* Codifico lunghezza stringa1 come intero unsigned a 16 bit in formato
                            * big endian (AKA network byte order) */

                            memset(len,0,sizeof(len));
                            dim_response = strlen(response);
                            len[0] = (dim_response & 0xFF00) >> 8;
                            len[1] = (dim_response & 0xFF);

                            /* Invio lunghezza prima stringa */
                            if (write_all(ns, len, 2) < 0) {
                                    perror("write");
                                    exit(EXIT_FAILURE);
                            }

                            /* Invio prima stringa */
                            if (write_all(ns, response, dim_response) < 0) {
                                    perror("write");
                                    exit(EXIT_FAILURE);
                            }
                    }

                    /* Chiudo la socket attiva */
                    close(ns);

                    /* Termino il figlio */
                    exit(EXIT_SUCCESS);
            }

            /* PADRE */

            /* Chiudo la socket attiva */
            close(ns);
    }
}
