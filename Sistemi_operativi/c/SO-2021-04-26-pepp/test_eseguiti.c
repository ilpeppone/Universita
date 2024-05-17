#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#define DIM_NOME 20

static volatile sig_atomic_t n_byte;

void handler(){
    printf("Numero totali di byte ricevuti da p2: %d",n_byte);
}

int main(int argc, char **argv){
    int fd,pid,p0p1[2],p0p2[2],status;
    char data[9], nome[DIM_NOME];
    if(argv!=3){
        fprintf(stderr,"Uso: %s dir data",argv[0]);
        exit(-1);
    }

    if(argv[1][0]=='/'){
        fprintf(stderr,"Inserire un percorso relativo");
        exit(-2);
    }

    sprintf(data,"%s/%s",argv[1],argv[2]);

    if((fd=open(data,O_RDONLY))<0){
        perror("Errore apertura file\n");
        exit(-2);
    }
    close (fd);

    signal(SIGINT,handler);

    printf("Chi ha refertato il test ('fine' per terminare):\t");
    scanf("%s",nome);


    if(pipe(p0p1)<0){
        perror("Errore p0p1");
        exit(-3);
    }
    if(pipe(p0p2)<0){
        perror("Errore p0p1");
        exit(-3);
    }
    if(pid=fork()<0){
        perror("Errore fork p1");
        exit(-4);
    }
    if (pid==0){

        close(p0p1[1]);

        close(p0p2[0]);

        signal(SIGINT,SIG_DFL);

        while(strcmp(nome,"fine")){
            
        }






    }
    return 0;
}
    

