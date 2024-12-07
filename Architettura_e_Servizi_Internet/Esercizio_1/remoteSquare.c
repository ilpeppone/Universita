#define _POSIX_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include "utils.h"

int main(int argc,char **argv){
    if (argc!=3){
        fprintf(stderr,"Uso: ./remoteSquare hostname porta\n");
        exit(EXIT_FAILURE);
    }
    
    char numero[__UINT16_MAX__];
    int err,sd;
    struct addrinfo hints,*ptr,*res;

    signal(SIGPIPE,SIG_DFL);

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;

    err=getaddrinfo(argv[1],argv[2],&hints,&res);
    if(err!=0){
        fprintf(stderr,"Errore risoluzione nome %s\n",gai_strerror(err));
        exit(EXIT_FAILURE);
    }
    
    /*connessione con fallback*/
    for(ptr=res;ptr!=NULL;ptr=ptr->ai_next){
        sd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        /*se la socket fallisce passa all'indirizzo successivo*/
        if(sd<0)
            continue;
            /*se la connessione va a buon fine esco dal ciclo*/
        if(connect(sd,ptr->ai_addr,ptr->ai_addrlen)==0)
            break;
        close(sd);
    }
     /*controllo che il client sia effettivamente connesso*/
    
    if(ptr==NULL){
        fprintf(stderr,"Errore di connessione");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);




}

