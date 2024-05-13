#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#define DIM1 7

volatile sig_atomic_t counter;

void terminazione_programma(){
    printf("Numero di richieste %d", counter);
    exit(0);
}

int main(int argc,char **argv){
    int fd,pid1,pid2,p2p0[2];
    char nome_file[DIM1];

    if (argc!=2){
        fprintf(stderr,"Uso: trova_video.c dir");
        exit(1);
    }
    if (argv[1][0] == '/'){
        fprintf(stderr,"Errore, non si tratta di un percorso realtivo di direttorio");
        exit(2);
    }

    if ((fd=open(argv[1],__O_DIRECTORY))<0){
        perror("Errore apertura cartella");
        exit(3);
    }
    close(fd);
    //dichiaro
    signal(SIGINT,terminazione_programma); //SIG_* handler //SIGINT tipologia segnale //da 33 in poi segnali del padre
    // signal(SIGINT,SIG_DFL);   //quando arriva il sigint viene eseguita la funzione di default(chiusura forzata) //da mettere come prima riga dei figli, dopo la fork
    if(pipe(p2p0[2])<0){    //fuori dalle fork
        perror("Errore p2p0");
        exit(5);
    }
    
    if((pid1=fork())==0){
        signal(SIGINT,SIG_DFL);
        if((pid2=fork())==0){
            // non c'e bisogno di scrivere signal dato che lo eredita da pid1
        
        }
    }
    
    if((pid2=fork())==0){
        signal(SIGINT,SIG_DFL);
            // non c'e bisogno di scrivere signal dato che lo eredita da pid1
        
        }
    




}