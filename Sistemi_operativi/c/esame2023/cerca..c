#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>


void handler_count(){

}


int main(int argc,char **argv){
    int pid,fd;

    if(argc != 2){
        printf("Uso: %s percorso dir\n");
        exit(1);
    }
    if(argv[1][0] != "/"){
        printf("Errore: %s non si tratta di un percorso assoluto\n",argv[1]);
        exit(2);
    }
    if((fd=open(argv[1], O_DIRECTORY))<0){
        perror("Errore nell'apertura della cartella\n");
        exit(3);
    }
    close (fd);

    signal(SIGINT,handler_count);



}