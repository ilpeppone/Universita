#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define DIM 50

int main(int argc,char *argv[]){
    int num,pid,status,fd;
    char nome[DIM];
    if (argc!=2){
        printf("Uso: ./anteprima.c num\n");
        exit(1);
    }

    if((num=atoi(argv[1]))<=0){
        printf("Errore. %s non è positivo maggiore di zero\n",argv[1]);
        exit(2);
    }
    
    printf("Inserisci il nome del file di cui vuoi verificarne l'anteprima ('fine' per uscire):\n");
    scanf("%s",nome);

    while(strcmp(nome,"fine")!=0){
        if((fd=open(nome,O_RDONLY))<0){
            if(errno==ENOENT){
            printf("Errore: il file %s non esiste\n",nome);
            } else {
                perror("open");
                exit(3);
            }
        } else {
            close(fd);
            pid=fork();
            if (pid<0){
                perror("fork");
                exit(4);
            } else if (pid==0){
                printf("\nAnteprima del file %s: ",nome);
                execl("/usr/bin/head","head","-n",argv[1],nome,(char *)0);

                perror("exec");
                exit(5);
            }
            wait(&status);
        }
        

    }
    return 0;
}