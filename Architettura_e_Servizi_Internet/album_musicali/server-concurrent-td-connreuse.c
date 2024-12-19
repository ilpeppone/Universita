#define _POSIX_C_SOURCE 200809L
#include <limits.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "rxb.h"
#include "utils.h"
#include <signal.h>

#define MAX_LINE_LENGTH 1024

int autorizza(const char *username,const char *password){
    return 1;
}

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
        fprintf(stderr,"Uso: ./%s porta",argv[0]);
        exit(EXIT_FAILURE);
    }

    err = sigaction(SIGPIPE,NULL,NULL);
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
    hints.ai_family =AF_UNSPEC;
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

    on = 1;
    err = setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    if(err<0){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    err = bind (sd,res->ai_addr,res->ai_addrlen);
    if(err<0){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);
    
    err = listen(sd,SOMAXCONN);
    if (err<0){
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
        if(pid_child<0){
            perror("fork");
            exit(EXIT_FAILURE);
        } else if(pid_child == 0){
            /*figlio*/
            rxb_t rxb;

            close(sd);
            rxb_init(&rxb,2*MAX_LINE_LENGTH);

            memset(&sa,0,sizeof(sa));
            sa.sa_handler = sigchld_handler;
            sa.sa_flags = SA_RESTART;
            sigemptyset(&sa.sa_mask);

             err = sigaction(SIGCHLD,&sa,NULL);
            if(err<0){
                perror("sigaction SIGCHLD");
                exit(EXIT_FAILURE);
            }

            for(;;){
                char username[MAX_LINE_LENGTH +1],password[MAX_LINE_LENGTH +1],artista[MAX_LINE_LENGTH +1];
                size_t username_len,password_len,artista_len;
                pid_t pid_n1,pid_n2;
                int pipe_n1n2[2];
                char filename[PATH_MAX +1];

                memset(username,0,sizeof(username));
                username_len=sizeof(username) -1;

                if(rxb_readline(&rxb,ns,username,&username_len)<0){
                    perror("rxb_readline username");
                    exit(EXIT_FAILURE);
                }
#ifdef USE_LIBUNISTRING
                if(((uint8_t *)response_line,response_line_len)!=NULL){
                fprintf(stderr,"ERRORE: Stringa username non testo UTF-8 valido\n");
                exit(EXIT_FAILURE);
            }
#endif
                memset(password,0,sizeof(password));
                password_len=sizeof(password) -1;

                if(rxb_readline(&rxb,ns,password,&password_len)<0){
                    perror("rxb_readline password");
                    exit(EXIT_FAILURE);
                }
#ifdef USE_LIBUNISTRING
                if(((uint8_t *)response_line,response_line_len)!=NULL){
                fprintf(stderr,"ERRORE: Stringa password non testo UTF-8 valido\n");
                exit(EXIT_FAILURE);
            }
#endif
                memset(artista,0,sizeof(artista));
                artista_len=sizeof(artista) -1;

                if(rxb_readline(&rxb,ns,artista,&artista_len)<0){
                    perror("rxb_readline artista");
                    exit(EXIT_FAILURE);
                }
#ifdef USE_LIBUNISTRING
                if(((uint8_t *)response_line,response_line_len)!=NULL){
                fprintf(stderr,"ERRORE: Stringa artista non testo UTF-8 valido\n");
                exit(EXIT_FAILURE);
            }
#endif  
                if(autorizza(username,password)!=1){
                    char *unauthorized = "Non autorizzato!\n";
                    char *end_request = "---END REQUEST---\n";
                    write_all(ns,unauthorized,strlen(unauthorized));
                    write_all(ns,end_request,strlen(end_request));
                    continue;
                }

                snprintf(filename,sizeof(filename),"./music/database_artisti.txt");

                if(pipe(pipe_n1n2)<0){
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }
                pid_n1 = fork();
                if(pid_n1<0){
                    perror("fork");
                    exit(EXIT_FAILURE);
                }else if(pid_n1==0){
                    /*nipote 1*/
                    close(1);
                    dup(pipe_n1n2[1]);
                    close(pipe_n1n2[1]);

                    close(pipe_n1n2[0]);
                    close(ns);

                    execlp("grep","grep",artista,filename,(char *)0);
                    perror("execlp grep");
                    exit(EXIT_FAILURE);
                }
                pid_n2 = fork();
                if(pid_n2<0){
                    perror("fork");
                    exit(EXIT_FAILURE);
                }else if(pid_n2==0){
                    /*Nipote 2*/
                    close(0);
                    dup(pipe_n1n2[0]);
                    close(pipe_n1n2[0]);
                    close(pipe_n1n2[1]);

                    close(1);
                    dup(ns);
                    close(ns);

                    execlp("sort","sort","-n","-r",(char *)0);
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
        }
        /*padre*/
        close(ns);
    }
    return EXIT_SUCCESS;
}
