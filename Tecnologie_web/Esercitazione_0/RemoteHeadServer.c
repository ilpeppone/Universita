#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "rbx.h"
#include <netdb.h> //per la getaddrinfo

/*Aussunzione 2: massima dimensione di una riga è 16kb*/
#define MAX_REQUEST_SIZE (16 * 1024) // 16kb
/*Aussunzione 2: massima dimensione di una riga è 4kb*/
#include MAX_LINE_LENGTH (4096)
int main (int argc, char *argv[]){
    struct addrinfo hints, *res;
    if (argc != 2){
        fprintf(stderr, "Usage: %s port\n",argv[0]);
        return EXIT_FAILURE;
    }
    /*inizializzazione hints*/
    memset(&hints,0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    /*chiamo getaddrinfo*/
    err = getaddrinfo(NULL, argv[1], &hints, &res);
    if( err != 0 ){
        fprintf(stderr, "Error (getaddrinfo): %s \n", gai_strerror(err));
        return EXIT_FAILURE;
    }

    sd = socket(res->ai_family, res ->ai_socktype, res->ai_protocol);
    if(sd <0){
        perror("socket");
        /*fprintf(stderr, "Error (socket): %s \n", strerror(errno));*/
        return EXIT_FAILURE;
    }

    opt = 1;
    err = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (err <0){
        perror ("setsockopt");
        return EXIT_FAILURE;
    }

    err = bind(sd, res-> ai_addr, res->ai_addrlen);
    if(err<0){
        perror("bind");
        return EXIT_FAILURE;
    }

    err = listen(sd, SOMAXCONN);
    if(err <0){
        perror("listen");
        return EXIT_FAILURE;
    }

    for(;;){
        int ns;
        rxb_t rxb_client;
        const size_t MAX_REQUEST_SIZE = (16 * 1024);//16kb
        ns = accept(sd,NULL,NULL);
        if(ns<0){
            /*if (errno = EINTR)
                continue;*/
            perror("accept");
            return EXIT_FAILURE;
        }
        /*server iterativo*/
        /*inizio servizio*/
        /*inizializzo buffer readline dal client*/
        rxb_init(&rxb_client, MAX_REQUEST SIZE * 2);
        char filename [ 2048];
        filename_len = sizeof(filename) - 1;//perchè le stringhe in c sono null terminator
        memset(filename,0, sizeof(filename));
        /*leggo filename*/
        err = rxv_readline(&rxb_client, ns, &filename, &filename_len);
        if (err <0){
            perror("rxb_readline");
            return EXIT_FAILURE;
        }
        /*apro filename*/
        int fd;
        fd = open (filename,O_RDONLY);
        if (fd <0 ){
            perror("open");
            return EXIT_FAILURE;
        }

        rxb_t rxb_file; 
        rxb_init(&rxb_client, (MAX_LINE_LENGTH +1)* 2);
        /*leggo le prime 5 righe del file e le mando al client*/
        for (i = 1; i<=5; ++i){
            char line[4096];//assunzione massima dimensione di una riga
            size_t line_len;
            
            memset(line, 0 , sizeof(line));
            line_len = sizeof()
        }
        /*denializzo */
        rxb_destroy(&rxb_file);
        rxb_destroy(&rxb_client);
        /*fine servizio*/
        close(ns);
    }
    close(sd);

    return EXIT_SUCCESS;

}

