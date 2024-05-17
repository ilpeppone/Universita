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
    int fd;
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

    

}