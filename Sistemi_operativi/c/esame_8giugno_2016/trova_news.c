#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#define DIM 50
void handler(int s){

}
int main(int argc, char **argv){
    int fd,pid1,pid2, data;
    char argomento[DIM],data[9];

    if(argc != 2){
        fprintf(stderr,"Uso: %s <dir>\n");
        exit(1);
    }

    if(argv[1][0]!='/'){
        fprintf(stderr,"Errore: %s non è un percorso di direttorio\n");
        exit(2);
    }

    if((fd=open(argv[1],O_DIRECTORY)) < 0){
        perror("Errore apertura cartella");
        exit(3);
    }

    printf("Inserisci argomento 'fine' per terminare: \n");
    scanf("%s",argomento);

    while(strcmp(argomento,"fine")){
        printf("Inserire data in formato YYYYMMDD:\n");
        scanf("%s",data);
    

        if ((pid1=fork())!=0){
            perror("Fork pid1");
            exit(4);
        }

        if(pid1==0){

        }




        printf("Inserisci argomento 'fine' per terminare: \n");
        scanf("%s",argomento);
    }
}