#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#ifdef USE_LIBUNISTRING
#include <unistr.h>
#endif
#include "utils.h"
#include "rxb.h"

#define MAX_LINE_LENGTH 1024

int main(int argc,char **argv){
    int err,sd;
    struct addrinfo hints,*res,*ptr;
    rxb_t rxb;

    signal(SIGPIPE,SIG_IGN);

    if(argc!=3){
        fprintf(stderr,"USO: ./%s hostname porta\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    err = getaddrinfo(argv[1],argv[2],&hints,&res);
    if(err!=0){
        fprintf(stderr,"Errore in getaddrinf:%s\n",gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    for(ptr = res; ptr!=NULL; ptr=ptr->ai_next){
        sd = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
        if(sd<0){
            continue;
        }
        err = connect(sd,ptr->ai_addr,ptr->ai_addrlen);
        if(err == 0){
            printf("Connessione riuscita!\n");
            break;
        }
        close(sd);
    }
    if(ptr==NULL){
        fprintf(stderr,"Errore: nessuna connessione riuscita\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    rxb_init(&rxb,2*MAX_LINE_LENGTH);
    
    for(;;){
        char data[MAX_LINE_LENGTH],sensore[MAX_LINE_LENGTH],stanza[MAX_LINE_LENGTH];

        printf("Inserisci la data YYYYMMDD ('fine' per terminare)\n");
        if(fgets(data,sizeof(data),stdin)==NULL){
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        if(strcmp(data,"fine\n")==0){
            break;
        }
        printf("Inserisci il nome del sensore('fine' per terminare)\n");
        if(fgets(sensore,sizeof(sensore),stdin)==NULL){
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        if(strcmp(sensore,"fine\n")==0){
            break;
        }printf("Inserisci la stanza dov'è posizionato ('fine' per terminare)\n");
        if(fgets(stanza,sizeof(stanza),stdin)==NULL){
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        if(strcmp(stanza,"fine\n")==0){
            break;
        }
        if(write_all(sd,data,strlen(data))<0){
            perror("write");
            exit(EXIT_FAILURE);
        }
        if(write_all(sd,sensore,strlen(sensore))<0){
            perror("write");
            exit(EXIT_FAILURE);
        }if(write_all(sd,stanza,strlen(stanza))<0){
            perror("write");
            exit(EXIT_FAILURE);
        }

        for(;;){
            char response_line[1024];
            size_t response_line_len;

            memset(response_line,0,sizeof(response_line));
            response_line_len=sizeof(response_line) - 1;

            err = rxb_readline(&rxb,sd,response_line,&response_line_len);
            if(err<0){
                perror("rxb_readline");
                exit(EXIT_FAILURE);
            }
#ifdef USE_LIBUNISTRING
            if (u8_check((uint8_t *)response_line,response_line_len)!=NULL){
                fprintf(stderr,"Stringa di risposta non testo UTF-8 valida\n");
                exit(EXIT_FAILURE);
            }
#endif 
            if(strcmp(response_line,"---END RESPONSE---")==0){
                break;
            }
            puts(response_line);
        }
    }
    rxb_destroy(&rxb);
    close(sd);
    return EXIT_SUCCESS;
}
