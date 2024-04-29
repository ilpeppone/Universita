#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define DIM 128
#define PATH 256
#define RES 16


typedef int pipe_t[2];
static volatile sig_atomic_t counter;

void handler(int s){
    printf("Ricevuto interrupt da tastiera, ricevute %d richieste...\n",counter);
    //zombies
    wait(&status);
    wait(&status);

    exit(0);

}

int main(int argc,char **argv){
    int fd,status, pid;
    ssize_t nread;
    pipe_t p1p2,p2p0;

    char cloud_provider[DIM],application_name[DIM],
    file_path[PATH],result_str[RES];
    
    if (argc!=2){
        printf("Uso: %s dir\n",argv[0]);
        exit(1);
    }
    if (argv[1][0] != "/"){
        printf("Errore! %s non e' un direttorio assoluto\n",argv[1]);
        exit(2);
    }
    
    if ((fd = open(argv[1], O_DIRECTORY)) < 0) {
        perror("Errore nell'apertura del directory");
        exit(3);
    }
    close(fd);

    signal(SIGINT,handler);

    printf("Inserire il nome di un Cloud provide, 'fine' per uscire\n");
    scanf("%s",cloud_provider);

    while(strcmp(cloud_provider,"fine")){
        sprintf(file_path,"%s/%s.txt",argv[1],cloud_provider);
        if((fd=open(file_path,O_RDONLY))<0){
            if(errno==ENOENT){
            printf("Errore: non esiste file chiamato %s \n",cloud_provider);
            printf("Inserire il nome di un altro file e riprovare,'fine' per terminare\n");
            scanf("%s",cloud_provider);
            continue;
            }
            perror("Errore tentando di aprire il nome del file specificato\n");
            exit(4);
        }
        close(fd);
        printf("Inserire il nome di un'applicazione: \n");
        scanf("%s",application_name);

        if (pipe(p1p2)<0){
            perror("pipe() p1p2\n");
            exit(5);
        }
        if ((pid=fork())<0){
            perror("fork() P1\n");
            exit(6);
        }
        else if (pid==0){
            signal(SIGINT,SIG_DFL);
            close (p1p2[0]);

            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);
            execlp("grep","grep",application_name,file_path,(char *) 0);
            perror("P1; execlp");
            exit(7);
        }

        close(p1p2[1]);
        if(pipe(p2p0)<0){
            perror("pipe() p2p0");
            exit(8);
        }
        if ((pid = fork ())<0){
            perror("fork () P2");
            exit(9);
        }
        else if(pid == 0){
            signal(SIGINT, SIG_DFL);
            close(p2p0[0]);

            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);
            
            
            close(1);
            dup(p2p0[1]);
            close(p2p0[1]);

            execlp("grep","grep","-c","operativa",(char *) 0);
            perror("P2; execlp");
            exit(10);
        }

        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p0[1]);

        nread = read (p2p0[0],result_str, RES-1);
        counter ++;
        
        wait(&status);
        wait(&status);

        printf("Inserire il nome di un Cloud Provider,'fine' per uscire\n");
        scanf("%s",cloud_provider);
    }

    printf("Numero di richieste servite: %u\n",counter);
    return 0;
}