#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define DIM 80

int main(int argc,char **argv){

    int p1p2[2];
    char matricola[DIM];
    int pid1, pid2, fd, status;
    if (argc != 2){
        fprintf(stderr,"Uso: %s <file_dati>\n",argv[0]);
        exit(1);
    }
    
    return (0);
}