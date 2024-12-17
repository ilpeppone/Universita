#define _POSIX_C_SOURCE 200809L
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
void sigchild_handler(int signo){
    (void)signo;
    int status;
    /*deallocazione di tutti i figli teminati
    *(con wait solo le risorse del primo)*/
    while(waitpid(-1,&status,WNOHANG)>0)
        continue;
}
int main(int argc,char **argv){
    int err,sd,on;
    struct addrinfo hints,*res,*ptr;
    struct sigaction sa;
    if(argc!=2){
        fprintf(stderr,"Uso: %s port\n",argv[0]);
        return EXIT_FAILURE;
    }
    /*ignoro il sigpipe*/
    signal (SIGPIPE,SIG_IGN);

    memset(&sa,0,sizeof(sa));
    sa.sa_handler =  sigchild_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    /*chiamo getaddrinfo*/
    err = getaddrinfo(NULL,argv[1],&hints,&res);
    if (err != 0){
        printf(stderr,"Errore in getaddrinfo: %s\n",gai_strerror(err));
        return EXIT_FAILURE;
    }
    /*creao socket*/
    sd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if(sd<0){
        perror("socket");
        return EXIT_FAILURE;
    }
    /*disabilito time_wait*/
    on=1;
    err=setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));



    freeaddrinfo(res);
    err=listen(sd,SOMAXCONN);
    if(err<0){
        perror("listen");
        return EXIT_FAILURE;
    }

    return 0;
}