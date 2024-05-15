#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define DIM 16
#define BUFFDIM 256

static volatile sig_atomic_t byte_p2 = 0;

void handler(int s){
    printf("Byte letti dal processo P2: %d\n",byte_p2);
    exit(1);
}

int main (int argc, char **argv){
    int fd,p1,p2,p1p2[2],p2p0[2];
    char cognome[DIM],libro[DIM*4],buff[BUFFDIM];
    if (argc!=2){
        fprintf(stderr,"Uso: controllo dir");
        exit(-1);
    }

    if (argv[1][0]!='/'){
        fprintf(stderr,"Errore: %s non è un direttorio assoluto",argv[1]);
        exit(-2);
    }

    if((fd=open(argv[1],O_DIRECTORY))<0){
        fprintf(stderr,"Errore durante l'apertura del direttorio");
        exit(-3);
    } 

    close(fd);

    SIGNAL(SIGINT,handler);

    printf("Inserisci cognome dell'autore ('fine' per terminare): \n");
    scanf("%s",cognome);

    printf("Inserisci titolo del libro:  \n");
    scanf("%s",libro);

    while(strcmp(cognome,"fine")){
        if(pipe(p1p2)<0){
            perror("Errore p1p2");
            exit(-4);
        }
        if((p1=fork())<0){
            perror("Errore fork p1");
            exit(-5);
        }

        if (p1==0){
            char path_libro [DIM*5];
            sprintf(path_libro, "%s/%s/%s",argv[1],cognome,libro);
            printf("File da ricercare: %s\n",path_libro);

            if((fd=open(path_libro,O_RDONLY))<0){
                perror("Non esiste un file corrispondente");
                continue;
            }
            close (fd);

            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("/usr/bin/sort","sort -n -r",path_libro,(char * )0);
            perror("Errore sort");
            exit(-6);
        }
        if(pipe(p2p0)<0){
            perror("Errore p2p0");
            exit(-7);
        }
        if((p2=fork())<0){
            perror("Fork p2");
            exit(-8);
        }

        if(p2==0){
            close(p1p2[1]);

            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            close(p2p0[0]);
            close(1);
            dup(p2p0[1]);
            close(p2p0[1]);

            execlp("/usr/bin/grep","grep","ingresso",(char *)0);
            perror("Errore grep");
            exit(-9);
        }

        close(p1p2[0]);
        close(p1p2[1]);

        close(p2p0[1]);

        int byte_ricerca=0;

        memset(buff, 0, BUFFDIM);
        while((byte_ricerca = read(p2p0[0], buff, sizeof(buff))) > 0){
            write(1, buff, byte_ricerca);
            byte_p2 += byte_ricerca;
            memset(buff, 0, BUFFDIM);
        }
        printf("Inserisci cognome dell'autore ('fine' per terminare): \n");
        scanf("%s",cognome);

        printf("Inserisci titolo del libro:  \n");
        scanf("%s",libro);
    }
        printf("Numero totale di byte letti da P2 %d\n", byte_p2);
        
    return 0;
}