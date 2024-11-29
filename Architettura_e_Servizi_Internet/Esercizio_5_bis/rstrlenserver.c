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

    
}