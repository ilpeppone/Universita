#define _POSIX_C_SOURCE 200809L
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "rxb.h"
#include "utils.h"

#define MAX_LINE_LENGTH 1024


void sigchld__handler(int signo){
    int status;
    (void)signo;

    while(waitpid(-1,&status,WNOHANG)>0)
        continue;
}


int main (int argc,char **argv){
    int err,sd,on;
    struct addrinfo hints,*res;
    struct sigaction sa;

    if(argc!=2){
        fprintf(stderr,"Uso: %s porta\n",argv[0]);
        return EXIT_FAILURE;
    }
    
    err=sigaction(SIGPIPE,NULL,NULL);
    if(err<0){
        perror("sigaction SIGPIPE");
        return EXIT_FAILURE;
    }
    
    memset(&sa,0,sizeof(sa));
    sa.sa_handler = sigchld__handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    err=sigaction(SIGCHLD,&sa,NULL);
    if(err<0){
        perror("sigaction SIGCHLD");
        return EXIT_FAILURE;
    }

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    err=getaddrinfo(NULL,argv[1],&hints,&res);
    if(err!=0){
        fprintf(stderr,"Errore in getaddrinfo: %s\n",gai_strerror(err));
        return EXIT_FAILURE;
    }
    sd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if(sd<0){
        perror("socket");
        return EXIT_FAILURE;
    }

    on = 1;
    err = setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    if(err<0){
        perror("setsockopt");
        return EXIT_FAILURE;
    }
    
    err=bind(sd,res->ai_addr,res->ai_addrlen);
    if(err<0){
        perror("errore bind");
        return EXIT_FAILURE;
    }
    freeaddrinfo(res);

    err=listen(sd,SOMAXCONN);
    if(err<0){
        perror("listen");
        return EXIT_FAILURE;
    }
    for(;;){
        int ns=accept(sd,NULL,NULL);
        if(ns<0){
            perror("accept");
            return EXIT_FAILURE;
        }

        pid_t pid_child = fork();

        if(pid_child<0){
            perror("fork");
            return EXIT_FAILURE;
        } else if (pid_child==0){
            /*figlio*/
            rxb_t rxb;
            close(sd);
            /*inizializzo buffer rxb_readline*/
            rxb_init(&rxb,2*MAX_LINE_LENGTH);
            /*reinstallo gestore default sigchild*/
            memset(&sa,0,sizeof(sa));
            sa.sa_handler=sigchld__handler;
            sa.sa_flags=SA_RESTART;
            sigemptyset(&sa.sa_mask);

            err = sigaction(SIGCHLD,&sa,NULL);
            if(err<0){
                perror("sigaction SIGCHLD");
                return EXIT_FAILURE;
            }
            /*ciclo richieste */
            for(;;){
                char mese[MAX_LINE_LENGTH + 1];
                char categoria[MAX_LINE_LENGTH + 1];
                char numero_spese[MAX_LINE_LENGTH +1];
                size_t mese_len,categoria_len,numero_spese_len;
                char filename[PATH_MAX+1];
                pid_t pid_p1,pid_p2,pid_p3;
                int pipe_p1p2[2],pipe_p2p3[2];

                memset(mese,0,sizeof(mese));
                mese_len=sizeof(mese) - 1;
                /*leggo mese*/
                if(rxb_readline(&rxb,ns,mese,&mese_len)<0){
                    perror("rxb_readline");
                    return EXIT_FAILURE;
                }
#ifdef USE_LIBUNISTRING
            if(u8_check((uint8_t *)mese,mese_len)!=NULL){
                fprintf("Errore stringa mese non testo UTF-8 valido\n");
                return EXIT_FAILURE;
            }
#endif
                memset(categoria,0,sizeof(categoria));
                categoria_len = sizeof(categoria)-1;
                if(rxb_readline(&rxb,ns,categoria,&categoria_len)<0){
                    perror("rxb_readline");
                    return EXIT_FAILURE;
                }
#ifdef USE_LIBUNISTRING
            if(u8_check((uint8_t *)categoria,categoria_len)!=NULL){
                fprintf("Errore stringa categoria non testo UTF-8 valido\n");
                return EXIT_FAILURE;
            }
#endif
                memset(numero_spese,0,sizeof(numero_spese));
                numero_spese_len=sizeof(numero_spese) - 1;
                /*leggo mese*/
                if(rxb_readline(&rxb,ns,numero_spese,&numero_spese_len)<0){
                    perror("rxb_readline");
                    return EXIT_FAILURE;
                }
#ifdef USE_LIBUNISTRING
            if(u8_check((uint8_t *)numero_spese,numero_spese_len)!=NULL){
                fprintf("Errore stringa numero_spese non testo UTF-8 valido\n");
                return EXIT_FAILURE;
            }
#endif
                /*stringa filename*/
                /*utilizzo il percorso expenses/202009/cancelleria.txt al posto di 
                * /var/local/expenses/202009/cancelleria.txt*/
                snprintf(filename,sizeof(filename),"./expenses/%s/%s.txt",mese,categoria);

                if(pipe(pipe_p1p2)<0){
                    perror("pipe");
                    return EXIT_FAILURE;
                }
                pid_p1 = fork();
                if(pid_p1<0){
                    perror("fork");
                    return EXIT_FAILURE;
                } else if(pid_p1 == 0){
                    /*sono nel nipote*/
                    /*cut -d  "," filename*/
                    close(1);
                    dup(pipe_p1p2[1]);

                    close(pipe_p1p2[1]);
                    close(pipe_p1p2[0]);
                    close(ns);

                    execlp("cut","cut","-d",",", filename,(char *)NULL);
                    perror("execlp cut");
                    return EXIT_FAILURE;
                }
                if(pipe(pipe_p2p3)<0){
                    perror("pipe");
                    return EXIT_FAILURE;
                }
                pid_p2 = fork();
                if(pid_p2<0){
                    perror("fork");
                    return EXIT_FAILURE;
                }else if(pid_p2==0){
                    /*nipote 2*/
                    /*sort -n -r*/

                    close(0);
                    dup(pipe_p1p2[0]);
                    close(pipe_p1p2[0]);
                    close(pipe_p1p2[1]);

                    close(1);
                    dup(pipe_p2p3[1]);
                    close(pipe_p2p3[1]);
                    close(pipe_p2p3[0]);

                    close(ns);
                    
                    execlp("sort","sort","-n","-r",(char *)0);
                    perror("execlp sort");
                    return EXIT_FAILURE;
                }
                pid_p3 = fork();
                if(pid_p3<0){
                    perror("fork");
                    return EXIT_FAILURE;
                }else if(pid_p3==0){
                    /*nipote 3*/
                    /*head -n numero_spese*/
                    close(pipe_p1p2[0]);
                    close(pipe_p1p2[1]);

                    close(0);
                    dup(pipe_p2p3[0]);
                    close(pipe_p1p2[0]);
                    close(pipe_p2p3[1]);

                    close(1);
                    dup(ns);
                    close(ns);

                    execlp("head","head","-n",numero_spese,(char *)0);
                    perror("execlp head");
                    return EXIT_FAILURE;
                }

                char *stringa_terminazione = "---END RESPONSE---\n";

                close(pipe_p1p2[0]);
                close(pipe_p1p2[1]);
                close(pipe_p2p3[0]);
                close(pipe_p2p3[1]);

                waitpid(pid_p1, NULL, 0);
                waitpid(pid_p2, NULL, 0);
                waitpid(pid_p3, NULL, 0);

                /*scrivo messaggio fine risposta*/
                err = write_all(ns,stringa_terminazione,strlen(stringa_terminazione));
                if(err<0){
                    perror("write_all");
                    return EXIT_FAILURE;
                }
            }
            rxb_destroy(&rxb);
        }
        close(ns);
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}