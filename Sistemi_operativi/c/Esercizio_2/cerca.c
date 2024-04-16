#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
int main(int argc, char *argv[]){
//cerca <nomefile> <stringa1> ... <stringaN>
    int pid,status;
    if(argc<3){
        fprintf(stderr,"Uso: cerca <nomefile> <stringa1> ... <stringaN>\n");
        exit(1);
    }

    int fd=open("conteggio.txt", O_CREAT |  O_TRUNC| O_WRONLY ,0644);

    if(fd<0){
        perror("Errore nella creazione del file di conteggio\n");
        exit(2);
    }

    close(fd);

    for(int i=2;i<argc;i++){

        pid=fork();

        if (pid<0){
            perror("Errore fork\n");
            exit(3);
        } else if(pid==0){
            //figlio

        fd=open("conteggio.txt",O_WRONLY |O_APPEND);
        char log [256];
        //creao log conteggio
        sprintf(log,"%s %s\n",argv[1],argv[i]);
        //scrivo log su file
        write(fd,log,strlen(log));
        close(fd);
        printf("\nNumero di righe in cui compare la stringa %s: \n",argv[i]);
        //chiamata a grep -c stringa nomefile
        execl("/bin/grep","grep","-c",argv[i],argv[1],(char* )0);
        perror("exec");
        exit(4);
        }

    }

    // Se arrivo qui, sono sicuramente il padre
	for(int i = 2; i < argc; i++) {
		/* Padre - Attendo la terminazione di uno dei figli */
		wait(&status);
	}
	
	/* Esco senza errori */
	return 0;



}