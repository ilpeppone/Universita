#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define COG 30 
#define PRE 7
static volatile sig_atomic_t count=0;

void handler(){
    printf("Numero di richieste effettuate: %d\n",count);
}

int main (int argc,char **argv){
    int fd,pid,p1p2[2],status;
    char cognome[COG],prefisso[PRE];
    if(argc!=2){
        fprintf(stderr,"Uso: %s fileAnagrafica\n",argv[0]);
        exit(-1);
    }

    if (argv[1][0]!='/'){
        fprintf(stderr,"Errore: %s non è un percorso assoluto di file\n",argv[1]);
        exit(-2);
    }

    if((fd=open(argv[1],O_RDONLY))<0){
        fprintf(stderr,"Errore apertura file\n");
        exit(-3);
    }
    close(fd);

    signal(SIGINT,handler);

    

    while(1){
        printf("Inserisci il cognome da ricercare\n");
        scanf("%s", cognome);

        if (!strcmp(cognome, "fine") ) break;

        printf("Inserirsci il prefisso di interesse\n");
        scanf("%s", prefisso);

        if (!strcmp(prefisso, "fine")) break;

        if(pipe(p1p2)<0){
            perror("Errore pipe\n");
            exit(-4);
        }

        if((pid=fork())<0){
            perror("Errore fork1\n");
            exit(-5);
        }
        if(pid==0){
            signal (SIGINT,SIG_DFL);
            close(p1p2[1]);

            close(1);
            dup(p1p2[0]);
            close(p1p2[0]);

            execlp("grep","grep",cognome,(char *)0);
            perror("Grep 1\n");
            exit(-6);
        }

        
        if((pid=fork())<0){
            perror("Errore fork2\n");
            exit(-5);
        }

        if(pid==0){
            signal(SIGINT,SIG_DFL);

            close(p1p2[0]);
            
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);
            

            execlp("grep","grep",prefisso,(char *)0);
            perror("Grep 2\n");
            exit(-6);
        }
        close(p1p2[0]);
        close(p1p2[1]);

        wait(&status);
        wait(&status);
        count ++;
    
        
    }
    printf("Numero di richieste effettuate: %d\n",count);
    return 0;
}