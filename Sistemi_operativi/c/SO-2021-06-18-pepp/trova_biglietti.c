#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

static volatile sig_atomic_t n_richieste;

void handler(int s){
    printf("Il numero di richieste servite è: %d\n",n_richieste);
    exit(0);
}

int main(int argc,char **argv){
    int n,fd,giorno,mese,anno,p1,p2,p3;

    if(argc!=3){
        fprintf(stderr,"Uso: %s luogo N\n",argv[0]);
        exit(-1);
    }

    if(n=(atoi(argv[2]))<=0){
        fprintf(stderr,"Errore: N non è un numero intero positivo\n");
        exit(-2);
    }

    if((fd=open("/var/local/ticket/%s",argv[1],O_RDONLY))<0){
        perror("Errore apertura file\n");
        exit(-3);
    }
    close(fd);

    signal(SIGINT,handler);

    printf("Inserisci giorno mese ed anno separati da spazio ('-1' in uno qualsiasi per terminare):");
    scanf("%d%d%d",giorno,mese,anno);

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

        if((p1=fork())<0){
            perror("Errore fork p1");
            exit(-4);
        }
        
            
    }

    return 0;
}