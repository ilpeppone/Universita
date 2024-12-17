#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/errno.h>
#include "utils.h"

int main(int argc,char **argv){
    uint8_t buffer[2048];
    uint8_t len[2];
    int sd,err,nread;
    struct addrinfo hints,*res,*ptr;
    char email[512];
    char password[512];
    int email_len;
    int password_len;
    if(argc!=3){
        fprintf(stderr,"USO: ./lista_articoli server porta\n");
        exit(EXIT_FAILURE);
    }
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    err=getaddrinfo(argv[0],argv[1],&hints,&res);
    if (err) {
    fprintf(stderr, "Errore getaddrinfo: %s\n", gai_strerror(err));
    exit(EXIT_FAILURE);
    }

    for (ptr = res; ptr != NULL; ptr = ptr->ai_next) {
        sd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sd < 0)
            continue;
        err = connect(sd, ptr->ai_addr, ptr->ai_addrlen);
        if (err == 0)
            break;
        /* Chiudo la socket e provo prossima struttura */
        close(sd);
    }

    if (ptr == NULL) {
    fputs("Errore di connessione", stderr);
    exit(EXIT_FAILURE); 
    }
    /* Libero memoria */ 
    freeaddrinfo(res);

    printf("Digita e-mail:\n");
    if (scanf("%s", email) == EOF || errno != 0) {
    perror("scanf");
    exit(EXIT_FAILURE);
    }

    printf("Digita password:\n");
    if (scanf("%s", password) == EOF || errno != 0) {
    perror("scanf");
    exit(EXIT_FAILURE);
    }

    /* Trasmetto username */
    email_len = strlen(email);
    if (email_len > UINT16_MAX) {
            fprintf(stderr, "E-mail troppo grande (massimo %d byte)!\n", UINT16_MAX);
            exit(EXIT_FAILURE);
    }

    /* Codifico lunghezza stringa1 come intero unsigned a 16 bit in formato
        * big endian (AKA network byte order) */
    len[0] = (uint8_t)((email_len & 0xFF00) >> 8);
    len[1] = (uint8_t)(email_len & 0xFF);

    /* Invio lunghezza username */
    if (write_all(sd, len, 2) < 0) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    /* Invio username */
    if (write_all(sd, email, email_len) < 0) {
        perror("write");
        exit(EXIT_FAILURE);
    }

        /* Trasmetto password */
    password_len = strlen(password);
    if (password_len > UINT16_MAX) {
        fprintf(stderr, "Password troppo grande (massimo %d byte)!\n", UINT16_MAX);
        exit(EXIT_FAILURE);
    }

        /* Codifico lunghezza stringa1 come intero unsigned a 16 bit in formato
        * big endian (AKA network byte order) */
    len[0] = (uint8_t)((password_len & 0xFF00) >> 8);
    len[1] = (uint8_t)(password_len & 0xFF);

        /* Invio lunghezza password */
    if (write_all(sd, len, 2) < 0) {
        perror("write");
        exit(EXIT_FAILURE);
    }

        /* Invio password */
    if (write_all(sd, password, password_len) < 0) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    
    /* Leggo ACK */
    if (read_all(sd, buffer, 4) < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    /* Verifico ACK */
    if (buffer[0] !=  0  || buffer[1] !=  2 || buffer[2] != 'O' || buffer[3] != 'K') {
    printf("Non autorizzato!\n");
    close(sd);
    exit(EXIT_SUCCESS);
    }

    while(1){
        char articolo[512];
        int articolo_len;

        printf("Digita articolo ('fine' per terminare):\n");
        if (scanf("%s", articolo) == EOF || errno != 0) {
        perror("scanf");
        exit(EXIT_FAILURE);
        }

        /* Per non aver problemi con write */
        fflush(stdout);

        if (strcmp(articolo, "fine") == 0) {
                break;
        }

        /* Trasmetto articolo */
        articolo_len = strlen(articolo);
        if (articolo_len > UINT16_MAX) {
        fprintf(stderr, "articolo troppo grande (massimo %d byte)!\n", UINT16_MAX);
        exit(EXIT_FAILURE);
        }

        /* Codifico lunghezza stringa1 come intero unsigned a 16 bit in formato
            * big endian (AKA network byte order) */
        len[0] = (uint8_t)((articolo_len & 0xFF00) >> 8);
        len[1] = (uint8_t)(articolo_len & 0xFF);

        /* Invio lunghezza articolo */
        if (write_all(sd, len, 2) < 0) {
        perror("write");
        exit(EXIT_FAILURE);
        }

        /* Invio articolo */
        if (write_all(sd, articolo, articolo_len) < 0) {
        perror("write");
        exit(EXIT_FAILURE);
        }

        /* Leggo lunghezza risposta */
        if (read_all(sd, len, 2) < 0) {
        perror("read");
        exit(EXIT_FAILURE);
        }

        size_t risposta_len = ((size_t)len[0]) << 8 | (size_t)len[1];
        size_t to_read = risposta_len;

        /* Stampo contenuto risposta a video */
        while (to_read > 0) {
            size_t bufsize = sizeof(buffer);
            size_t sz = (to_read < bufsize) ? to_read : bufsize;

            nread = read(sd, buffer, sz);
            if (nread < 0) {
            perror("read");
            exit(EXIT_FAILURE);
            }

            if (write_all(1, buffer, nread) < 0) {
            perror("write");
            exit(EXIT_FAILURE);
            }

            to_read -= nread;
        }

        /* Stampo un \n prima di terminare */
        if (write(1, "\n", 1) < 0) {
        perror("write");
        exit(EXIT_FAILURE);
        }
    }
    close(sd);
    return 0;
}