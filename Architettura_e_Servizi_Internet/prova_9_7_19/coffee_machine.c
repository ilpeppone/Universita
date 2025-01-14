#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"
#include "rxb.h"

#define DIM 80
#define MAX_REQUEST_SIZE 4096

int main(int argc,char**argv){
    struct addrinfo hints,*res,*ptr;
    rxb_t rxb;
    int err,sd;

    if (argc!=3){
        fprintf(stderr,"Uso: ./coffee_machine server porta\n");
        exit(EXIT_FAILURE);
    }

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    err = getaddrinfo(argv[1],argv[2],&hints,&res);

    if(err!=0){
        exit(EXIT_FAILURE);
    }

    for(ptr = res;ptr!=NULL;ptr = ptr->ai_next){
        sd=socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
        if(sd<0){
            continue;
        }
        err = connect(sd,ptr->ai_addr,ptr->ai_addrlen);
        if(err == 0)
            break;
        close(sd);
    }
    if(ptr == NULL){
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(res);

    rxb_init(&rxb, MAX_REQUEST_SIZE * 2);
    /*ciclo di servizio*/
    while(1){
        char username[DIM];
        char password[DIM];
        char categoria_macchina[DIM];
        char line [4086];
        puts("Inserisci username:");
        if(fgets(username,sizeof(username),stdin)==NULL){
            exit(EXIT_FAILURE);
        };//terminated data (prende \n)
        puts("Inserisci password:");
        if(fgets(password,sizeof(password),stdin)==NULL){
            exit(EXIT_FAILURE);
        };
        puts("Inserisci categoria macchine:");
        if(fgets(categoria_macchina,sizeof(categoria_macchina),stdin)==NULL){
            exit(EXIT_FAILURE);
        };
        if(write_all(sd,username, strlen(username))){
            exit(EXIT_FAILURE);
        }
        if(write_all(sd,password, strlen(password))){
            exit(EXIT_FAILURE);
        }
        if(write_all(sd,categoria_macchina, strlen(categoria_macchina))){
            exit(EXIT_FAILURE);
        }
        while(1){
            size_t buflen = sizeof(line)-1;
            memset(line,0,sizeof(line));

            err = rxb_readline(&rxb,sd,line,buflen);
            if(err<0){
                exit(EXIT_FAILURE);
            }
            if (strcmp(line,"--- END REQUEST ---") == 0)
                break;
            puts(line);
        }
    }
    rxb_destroy(&rxb);
    close(sd);
    return 0;
}