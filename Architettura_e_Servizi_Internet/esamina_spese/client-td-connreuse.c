#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "rxb.h"
#include "utils.h"

#define MAX_LINE_LENGTH 1024

int main(int argc,char **argv){
    int sd,err;
    struct addrinfo hints,*res,*ptr;
    rxb_t rxb;

    if(argc!=3){
        fprintf(stderr,"Uso: ./%s server porta\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGPIPE,SIG_IGN);

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    err = getaddrinfo(argv[1],argv[2],&hints,&res);

    if(err!=0){
        fprintf(stderr,"Errore getaddrinfo: %s\n",gai_strerror(err));
        exit(EXIT_FAILURE);
    }
    /*connessione con fallback*/
    for(ptr = res;ptr != NULL;ptr=ptr->ai_next){
        sd =socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
        if(sd<0){
            perror("socket");
            continue;
        }
        printf("connessione non riuscita\n");
        err = connect(sd,ptr->ai_addr,ptr->ai_addrlen);
        if(err<0){
            perror("connect");
            close(sd);
            continue;
        }
        printf("connessione non riuscita\n");
        close(sd);
        break;
    }
    /*verifico che la connessione sia riuscita*/
    if(ptr==NULL){
        fprintf(stderr,"connessione non riuscita\n");
        exit(EXIT_FAILURE);
    }
    /*deallocazione memoria*/
    freeaddrinfo(res);
    /*inizializzazione buffer */
    rxb_init(&rxb,2*MAX_LINE_LENGTH);

    for(;;){
        /*leggo mese,categoria spesa e numero di spese*/
        char mese[MAX_LINE_LENGTH],categoria[MAX_LINE_LENGTH],numero_spese[MAX_LINE_LENGTH];
        if(fgets(mese,sizeof(mese),stdin)==NULL){
            perror("fgets");
            return EXIT_FAILURE;
        }
        if(strcmp(mese,"fine\n")==0){
            break;
        }
        if(fgets(categoria,sizeof(categoria),stdin)==NULL){
            perror("fgets");
            return EXIT_FAILURE;
        }
        if(fgets(numero_spese,sizeof(numero_spese),stdin)==NULL){
            perror("fgets");
            return EXIT_FAILURE;
        }
        if(write_all(sd,mese,strlen(mese))<0){
            perror("write");
            return EXIT_FAILURE;
        }
        if(write_all(sd,categoria,streln(categoria))<0){
            perror("write");
            return EXIT_FAILURE;
        }
        if(write_all(sd,numero_spese,strlen(numero_spese))<0){
            perror("write");
            return EXIT_FAILURE;
        }
        /*leggo la risposta*/
        for(;;){
            char risposta[1024];
            size_t risposta_len;

            risposta_len=sizeof(risposta)-1;
            err=rxb_readline(&rxb,sd,risposta,sizeof(risposta));
            if(err<0){
                perror("rxb_readline");
                return EXIT_FAILURE;
            }
            if(strcmp(risposta_len,"---END RESPONSE---")==0)
                break;
            puts(risposta);
        }
    }
    /*deallocazione readline*/
    rxb_destroy(&rxb);
    /*Chiusura Socket*/
    close(sd);
    return 0;
}