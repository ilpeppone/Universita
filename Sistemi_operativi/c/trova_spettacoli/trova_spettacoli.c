#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>

#define DIM_PERCORSO 500
#define DIM_SPETTACOLO 100
#define DIM_RISPOSTA 2048

static volatile sig_atomic_t counter=0;
void handler(){
    printf("Richieste servite: %d\n",counter);
    exit(0);
}

int main(int argc,char **argv){
    int fd,n_spettacoli,pid,p1p2[2],p2p3[2],p0p3[2],n_read,status;
    char percorso[DIM_PERCORSO],spettacolo[DIM_SPETTACOLO],ris[DIM_RISPOSTA];
    if(argc!=2){
        fprintf(stderr,"Uso: %s <nome_teatro>\n",argv[0]);
        exit(-1);
    }
    sprintf(percorso,"/home/%s.txt",argv[1]);
    if((fd=open(percorso,O_RDONLY))<0){
        perror("Errore apertura file\n");
        exit(-2);
    }
    close(fd);

    signal(SIGINT,handler);

    printf("Inserisci il nome di uno spettacolo:\n");
    scanf("%s",spettacolo);
    printf("Inserisci il numero di spettacoli:\n");
    scanf("%d",&n_spettacoli);

    while (n_spettacoli!=0){
        if(pipe(p1p2)<0){
            perror("Errore creazione p1p2\n");
            exit(-3);
        }

        if((pid=fork())<0){
            perror("Fork p1\n");
            exit(-4);
        }
        if(pid==0){
            signal(SIGINT,SIG_DFL);
            //redirezione pipe
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep","grep",spettacolo,percorso,(char *)0);
            perror("Errore grep\n");
            exit(-5);
        }
        if(pipe(p2p3)<0){
            perror("Pipe p2p3\n");
            exit(-3);
        }
        if((pid=fork())<0){
            perror("Fork p2\n");
            exit(-4);
        }
        if(pid==0){
            signal(SIGINT,SIG_DFL);
            close(p1p2[1]);
            close(p2p3[0]);
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);
            close(1);
            dup(p2p3[1]);
            close(p2p3[1]);

            execlp("sort","sort","-n",(char *)0);
            perror("Errore sort\n");
            exit(-5);
        }
        if(pipe(p0p3)<0){
            perror("Errore creazione pipe p0p3\n");
            exit(-3);
        }
        if((pid=fork())<0){
            perror("Fork p3\n");
            exit(-4);
        }
        if(pid==0){
            signal(SIGINT,SIG_DFL);
            close(p1p2[0]);
            close(p1p2[1]);

            close(p2p3[1]);
            close(p0p3[0]);

            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);
            
            close(1);
            dup(p0p3[1]);
            close(p0p3[1]);
            
            char n_spettacoli_str[10];
            sprintf(n_spettacoli_str, "%d", n_spettacoli);

            execlp("head","head","-n",n_spettacoli_str,(char *)0);
            perror("Errore head\n");
            exit(-5);
        }
        
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p3[0]);
        close(p2p3[1]);
        close(p0p3[1]);
        wait(&status);
        wait(&status);
        wait(&status);
        n_read=read(p0p3[0],ris,sizeof(ris)-1);
        if(n_read<0){
            perror("P0: read\n");
            exit(-6);
        }
        close(p0p3[0]);
        ris[n_read]='\0';
        printf("%s\n",ris);
        
        counter++;

        printf("Inserisci il nome di uno spettacolo:\n");
        scanf("%s",spettacolo);
        printf("Inserisci il numero di spettacoli:\n");
        scanf("%d",&n_spettacoli);
    }


    printf("Richieste servite: %d\n",counter);
    return 0;
}