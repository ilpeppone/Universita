#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define ROOT_PATH "/home/studente"
#define DIM_PER 200
#define DIM_SPECT 200

static volatile sig_atomic_t count;

void handler(){
    printf("Numero di richieste servite: %d",count);
}

int main(int argc, char **argv){
    int fd,n_spettacoli,p1p2[2],p2p3[2],p0p3[2],pid;
    char percorso_file [DIM_PER],spettacolo[DIM_SPECT];

    if(argc!=2){
        fprintf(stderr,"Uso: %s nomeTeatro\n",argv[0]);
        exit(-1);
    }

    sprintf(percorso_file,"%s/%s",ROOT_PATH,argv[1]);

    if((fd=open("%s",percorso_file,O_RDONLY))<0){
        perror("Errore lettura\n");
        exit(-2);
    }
    close(fd);

    signal(SIGINT,handler);

    printf("Inserire nome di uno spettacolo:\t");
    scanf("%s",spettacolo);

    printf("Inserire numeri di spettacoli da trovare:\t");
    scanf("%d",n_spettacoli);

    while(n_spettacoli!=0){
        if(pipe(p1p2)<0){
            perror("Errore p1p2\n");
            exit(-3);
        }
        if((pid=fork())<0){
            perror("Errore fork p1\n");
            exit(-4);
        }
        if(pid==0){
            signal(SIGINT,SIG_DFL);

            close(p1p2[0]);

            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep","grep",spettacolo,(char *)0);
            perror("Error Grep\n");
            exit(-5);
        }
        if(pipe(p2p3)<0){
            perror("Errore p2p3\n");
            exit(-3);
        }
        if((pid=fork())<0){
            perror("Errore fork p2");
            exit(-4);
        }
        if(pid==0){

            close(p1p2[1]);
            close(p2p3[0]);

            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);
            
            
            close(1);
            dup(p2p3[1]);
            close(p2p3[1]);

            execlp("sort","sort","-n",(char *)0);
            perror("Errore sort\n");
            exit(-5);
        }
        if(pipe(p0p3)<0){
            perror("Errore p0p3\n");
            exit(-3);
        }
        if((pid=fork())<0){
            perror("Errore p3\n");
            exit(-4);
        }
        





    }

    return 0;
}