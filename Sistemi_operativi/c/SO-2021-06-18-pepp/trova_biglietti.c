#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#define DIM_FILEPATH 200
#define DIM_DATE 32

static volatile sig_atomic_t n_richieste;

void handler(){
    printf("Il numero di richieste servite è: %d\n",n_richieste);
    exit(0);
}

int main(int argc,char **argv){
    int n,fd,giorno,mese,anno,p1,p2,p3,p1p2[2],p2p3[2],status;
    char filepath[DIM_FILEPATH], date[DIM_DATE],strn_n[20];

    if(argc!=3){
        fprintf(stderr,"Uso: %s luogo N\n",argv[0]);
        exit(-1);
    }

    if((n=atoi(argv[2]))<=0){
        fprintf(stderr,"Errore: N non è un numero intero positivo\n");
        exit(-2);
    }

    sprintf(filepath,"/var/local/ticket/%s",argv[1]);

    if((fd=open(filepath,O_RDONLY))<0){
        perror("Errore apertura file\n");
        exit(-3);
    }
    close(fd);

    signal(SIGINT,handler);

    printf("Inserisci giorno mese ed anno separati da spazio ('-1' in uno qualsiasi per terminare):");
    scanf("%d%d%d",&giorno,&mese,&anno);

    while(1){
        if(giorno==-1||mese==-1||anno==-1)
            break;
        else if (giorno<0||mese<0||anno<0){
            printf("Inserire solo numeri positivi\n");
            continue;
        }
        else if (giorno>31||giorno<1){
            printf("Inserire un giorno valido\n");
            continue;
        }
        else if (mese<1||mese>12){
            printf("Inserire un mese valido\n");
            continue;
        }

        sprintf(date,"%02d%02d%04d",giorno,mese,anno);

        if(pipe(p1p2)<0){
            perror("Errore pipe p1p2");
            exit (-4);
        }
        if(pipe(p2p3)<0){
            perror("Errore pipe p2p3");
            exit(-4);
        }



        if((p1=fork())<0){
            perror("Errore fork p1");
            exit(-5);
        }

        if(p1==0){
            signal(SIGINT,SIG_DFL);
            // non serve,quindi chiudiamo la pipe p2p3
            close(p2p3[0]);
            close(p2p3[1]);
            // non serve perchè l'ingresso lo prendiamo dallo stdin
            close(p1p2[0]);
            // chiudiamo lo stdout, duplichiamo l'uscita della pipe p1p2 e la chiudiamo,dato che si trova in stdout
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep", "grep",date,filepath, (char *)0);
            perror("Errore grep");
            exit(-6);
            
        }

        if((p2=fork())<0){
            perror("Errore fork p2");
            exit(-6);
        }
        if(p2==0){
            signal(SIGINT,SIG_DFL);

            close(p1p2[1]);
            close(p1p2[0]);

            close(p2p3[0]);
            
            close(0);
            dup(p1p2[0]);

            close(p1p2[0]);

            close(1);
            dup(p2p3[1]);

            close(p2p3[1]);

            execl("sort","sort","-n",(char *)0);
            perror("Errore sort");
            exit(-6);
        }

        if((p3=fork())<0){
            perror("Errore fork p3");
            exit(-7);
        }
        if(p3==0){
            signal(SIGINT,SIG_DFL);

            close(p1p2[0]);
            close(p1p2[1]);

            close(0);
            dup(p2p3[0]);

            close(p2p3[0]);
            close(p2p3[1]);
            
            sprintf(strn_n,"%d",n);
            execl("head","head","-n",strn_n,(char *)0);
            perror("Error head");
            exit(-10);

        }

        close(p1p2[0]);
        close(p1p2[1]);

        close(p2p3[0]);
        close(p2p3[1]);

        wait(&status);
        wait(&status);
        wait(&status);

        n_richieste ++;
            
    }

    printf("Numero di richieste servite %d",n_richieste);
    return 0;
}