#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
    if (argc!=2){
        fprintf(stderr,"Usage: copy_input filename\n");
        exit(1);
    }
    char buff[1024];
    int fd = open(argv[1],O_WRONLY | O_TRUNC | O_CREAT , 0664);
    if (fd<0){
        fprintf(stderr,"Error creating file %s\n",argv[1]);
        exit(2);
    }

    printf("Inserisci una stringa: \n");
    fgets(buff,1024,stdin); //fgets, a differenza di fscanf prende anche gli spazi
    
    // se uso fgets avro' in buff anche il carattere di new line
    // se uso scanf faccio il controllo solo con "fine" (senza \n) 
    while(strcmp(buff,"fine\n")!=0){
        write(fd,buff,strlen(buff));
        printf("Inserisci una nuova stringa, 'fine' per uscire:\n");
        fgets(buff,1024,stdin);
    }

    close(fd);

    return 0;
}