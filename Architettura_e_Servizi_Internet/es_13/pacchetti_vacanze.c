#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "utils.h"
#include "rxb.h"
#define MAX_LINE_LENGTH 1024

/*client-td-connection reuse hostname porta
*                            argv[1]  argv[2]*/
int main(int argc,char **argv){
    /*controllo errori*/
    if(argc!=3){
        fprintf(stderr,"Uso:./pacchetti_vacanze.c server porta\n");
        exit(EXIT_FAILURE);
    }
    int sd,err;
    struct addrinfo hints,*res,*ptr;
    rxb_t rxb;
    /*ignoro sigpipe per evitare crash in caso di scrittura su socket chiusa*/
    signal(SIGPIPE, SIG_IGN);

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;

    err = getaddrinfo(argv[1],argv[2],&hints,&res);

    if(err!=0){
        fprintf(stderr,"Errore getaddrinfo: %s\n",gai_strerror(err));
        exit(EXIT_FAILURE);
    }
    
    /*connessione con fallback*/
    for(ptr = res;ptr!=NULL;ptr=ptr->ai_next){
        sd = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
        if(sd<0){
            perror("socket");
            continue;
        }
        printf("connessione riuscita\n");
        err=connect(sd,ptr->ai_addr,ptr->ai_addrlen);
        if(err<0){
            perror("connect");
            close(sd);
            continue;
        }
        printf("Connessione riuscita\n");
        close(sd);
        break;
    }
    /*verifico se la connessione è riuscita*/
    if(ptr==NULL){
        fprintf(stderr,"Errore: nessuna connessione riuscita\n");
        return EXIT_FAILURE;
    }
    /*deallocazione memoria*/
    freeaddrinfo(res);
    /*inizializzazione buffer all'interno della readline*/
    rxb_init(&rxb, 2*MAX_LINE_LENGTH);

    for(;;){
        /*leggo mese,tipologia e localita*/
        char mese[1024],tipologia[1024],localita[1024];

        if(fgets(mese,sizeof(mese),stdin)==NULL){
            perror("fgets");
            return EXIT_FAILURE;
        }
        if(strcmp(mese,"fine\n")==0){
            break;
        }
        if(fgets(tipologia,sizeof(tipologia),stdin)==NULL);
            perror("fgets");
            return EXIT_FAILURE;
        if(fgets(localita,sizeof(localita),stdin)==NULL);
            perror("fgets");
            return EXIT_FAILURE;
        if(write_all(sd,mese,strlen(mese))<0){
            perror("write");
            return EXIT_FAILURE;
        }
        if(write_all(sd,tipologia,strlen(tipologia))<0){
            perror("write");
            return EXIT_FAILURE;
        }
        if(write_all(sd,localita,strlen(localita))<0){
            perror("write");
            return EXIT_FAILURE;
        }
        /*leggo risposta*/
        for(;;){
            char risposta[1024];
            size_t risposta_len;

            risposta_len=sizeof(risposta)-1;
            err= rxb_readline(&rxb,sd,risposta,sizeof(risposta));
            if(err<0){
                perror("rxb_readline");
                return EXIT_FAILURE;
            }
            
            if(strcmp(risposta_len,"---END RESPONSE---")==0)
                break;
            puts(risposta);
        }
        
    }
    /*deallocazione*/
    rxb_destroy(&rxb);
    /*chiusura socket*/
    close(sd);
    return 0;
}