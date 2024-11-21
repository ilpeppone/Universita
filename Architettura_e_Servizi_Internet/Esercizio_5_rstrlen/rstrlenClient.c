#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

int main(int argc,char **argv){
    int sd,err,nread;
    uint8_t buffer[4096];
    struct addrinfo hints,*res,*ptr;

    if(argc!=3){
        fputs("Uso:./rstrlen hostname porta",stderr);
        exit(EXIT_FAILURE);
    }

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    err = getaddrinfo(argv[1],argv[2],&hints,&res);
    if(err!=0){
        fprintf(stderr,"Errore gai %s\n",gai_strerror(err));
        exit(EXIT_FAILURE);
    }
    
    for(ptr = res; ptr!=NULL; ptr=ptr->ai_next){
        sd = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
        if (sd<0) continue;

        err = connect(sd,ptr->ai_addr, ptr->ai_addrlen);
        if (err == 0) break;
        
        close (sd);
    }

    if(ptr == NULL){
        fputs("Errore connessione",stderr);
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);


    return 0;
}