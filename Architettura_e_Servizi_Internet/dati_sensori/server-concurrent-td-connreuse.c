#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "rxb.h"

#define MAX_LINE_LENGTH 1024

void sigchld_handler(int signo){
    int status;
    (void)signo;

    while(waitpid(-1,&status,WNOHANG)>0)
    continue;
}

int main(int argc,char **argv){
    int err,sd,on;
    struct addrinfo hints,*res;
    struct sigaction sa;

    if(argc!=2){
        fprintf(stderr,"Uso: ./%s porta\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    err=sigaction(SIGPIPE,NULL,NULL);
    if(err<0){
        perror("sigaction SIGPIPE");
        exit(EXIT_FAILURE);
    }

    memset(&sa,0,sizeof(sa));
    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    err = sigaction(SIGCHLD,&sa,NULL);
    if(err<0){
        perror("sigaction SIGCHLD");
        exit(EXIT_FAILURE);
    }

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    err = getaddrinfo(NULL,argv[1],&hints,&res);
    if(err!=0){
        fprintf(stderr,"Errore in getaddrinfo: %s\n",gai_strerror(err));
        exit(EXIT_FAILURE);
    }
    sd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if(sd<0){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    on=1;
    err = setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    if(err<0){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    err = bind(sd,res->ai_addr,res->ai_addrlen);
    if(err<0){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    err = listen(sd,SOMAXCONN);
    if(err<0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    for(;;){
        int ns = accept(sd,NULL,NULL);
        if(ns<0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        pid_t pid_child = fork();
        if (pid_child<0){
            perror("fork");
            exit(EXIT_FAILURE);
        }else if(pid_child==0){
            /*figlio*/
            rxb_t rxb;
            close(sd);
            rxb_init(&rxb,2*MAX_LINE_LENGTH);
            memset(&sa,0,sizeof(sa));
            sa.sa_handler = SIG_DFL;
            sa.sa_flags = SA_RESTART;
            sigemptyset(&sa.sa_mask);

            err = sigaction (SIGCHLD,&sa,NULL);
            if(err<0){
                perror("sigaction SIGCHLD");
                exit(EXIT_FAILURE);
            }
            for(;;){
                char data[MAX_LINE_LENGTH +1],sensore[MAX_LINE_LENGTH +1],stanza[MAX_LINE_LENGTH +1];
                size_t data_len,sensore_len,stanza_len;
                char filename[PATH_MAX +1];
                pid_t pid_n1, pid_n2;
                int pipe_n1n2[2];

                memset(data,0,sizeof(data));
                data_len=sizeof(data) -1;
                if(rxb_readline(&rxb,ns,data,&data_len)<0){
                    perror("rxb_readline data");
                    exit(EXIT_FAILURE);
                }
#ifdef USE_LIBUNISTRING
            if (u8_check((uint8_t *)data,data_len)!=NULL){
                fprintf(stderr,"Errore: stringa data UTF-8 non valida\n");
                exit(EXIT_FAILURE);
            }
#endif
                memset(sensore,0,sizeof(sensore));
                sensore_len=sizeof(sensore) -1;
                if(rxb_readline(&rxb,ns,sensore,&sensore_len)<0){
                    perror("rxb_readline sensore");
                    exit(EXIT_FAILURE);
                }
#ifdef USE_LIBUNISTRING
            if (u8_check((uint8_t *)sensore,sensore_len)!=NULL){
                fprintf(stderr,"Errore: stringa sensore UTF-8 non valida\n");
                exit(EXIT_FAILURE);
            }
#endif
                memset(stanza,0,sizeof(stanza));
                stanza_len=sizeof(stanza) -1;
                if(rxb_readline(&rxb,ns,stanza,&stanza_len)<0){
                    perror("rxb_readline stanza");
                    exit(EXIT_FAILURE);
                }
#ifdef USE_LIBUNISTRING
            if (u8_check((uint8_t *)stanza,stanza_len)!=NULL){
                fprintf(stderr,"Errore: stringa stanza UTF-8 non valida\n");
                exit(EXIT_FAILURE);
            }
#endif
            //utilizzo ./local al posto di /var/local
            snprintf(filename,sizeof(filename),"./local/%s/%s.txt",data,stanza);
            if(pipe(pipe_n1n2)<0){
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            pid_n1 = fork();
            if(pid_n1<0){
                perror("fork");
                exit(EXIT_FAILURE);
            }else if(pid_n1 == 0){
                /*nipote 1*/
                close(1);
                dup(pipe_n1n2[1]);
                close(pipe_n1n2[1]);

                close(pipe_n1n2[0]);
                close(ns);

                execlp("grep","grep",sensore,filename,(char *)0);
                perror("execlp grep");
                exit(EXIT_FAILURE);
            }

            pid_n2 = fork();
            if(pid_n2<0){
                perror("fork");
                exit(EXIT_FAILURE);
            } else if(pid_n2 == 0){
                /*nipote 2*/
                close(0);
                dup(pipe_n1n2[0]);
                close(pipe_n1n2[0]);
                close(pipe_n1n2[1]);
                
                close(1);
                dup(ns);
                close(ns);

                execlp("sort","sort","-n",(char *)0);
                perror("execlp sort");
                exit(EXIT_FAILURE);
            }
            /*figlio*/
            char *stringa_terminazione = "---END RESPONSE---\n";
            close(pipe_n1n2[0]);
            close(pipe_n1n2[1]);
            waitpid(pid_n1,NULL,0);
            waitpid(pid_n2,NULL,0);

            err = write_all(ns,stringa_terminazione,strlen(stringa_terminazione));
            if(err<0){
                perror("write_all");
                exit(EXIT_FAILURE);
            }
            }
            rxb_destroy(&rxb);

            close(ns);
            exit(EXIT_FAILURE);
        }
        /*padre*/
        close(ns);
    }
    return EXIT_SUCCESS;
}
