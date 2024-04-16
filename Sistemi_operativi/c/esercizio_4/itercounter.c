#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_PROC_NUM 20

static volatile sig_atomic_t contatore = 0;

void gestore(int signo){
    printf("Il processo %d ha eseguito %d iterazioni per il segnale %d\n",getpid(),contatore,signo);
    exit(0);
}

int main(int argc,char **argv){
    int *pid;
    int Nf,Nsec,status,i;
    if (argc!=3){
        fprintf(stderr, "Uso: ./itercounter <num_processi> <num_secondi>\n");
        exit(1);
    }

    Nf=atoi(argv[1]);
    if (Nf<=0){
        fprintf(stderr,"Il parametro <Nf> deve essere un valore positivo\n");
        exit(2);
    } 

    Nsec=atoi(argv[2]);
    if (Nsec<=0){
        fprintf(stderr,"Il parametro <Nsec> deve essere un valore positivo\n");
        exit(3);
    }

    pid= (int *) malloc (Nf * sizeof(int));
    for (i=0; i<Nf; ++i){
        pid[i]=fork();
        if (pid[i]<0){
            perror("Errore nella fork\n");
            exit(4);
        } else if (pid[i]==0){
            if (signal(SIGUSR1,gestore)==SIG_ERR){
                perror("Errore nella Signal, SIGUSER1 figlio\n");
                exit(-3);
            }
            while(1){
                sleep(1);
                contatore++;
            }
        }
    }
    sleep(Nsec);
    for (i=0;i<Nf;++i){
        kill(pid[i],SIGUSR1);
    }
    free(pid);
    for(i=0;i<Nf;i++){
        wait(&status);
    }
    return 0;
 }