#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#define ROOT_PATH "/var/local/ticket"
#define DIM_FILEPATH 200
#define DIM_DATE 11
static volatile sig_atomic_t counter=0;
void handler(){
    printf("Richieste servite: %d\n",counter);
}
int main(int argc, char **argv){
    int fd,n,gg,mm,aaaa,pid,p1p2[2],p2p3[2],status;
    char filepath[DIM_FILEPATH],date[DIM_DATE];
    if (argc!=3){
        fprintf(stderr,"Uso: %s destinazione N\n",argv[0]);
        exit(-1);
    }
    if ((n=atoi(argv[2]))<=0){
        fprintf(stderr,"Il numero deve essere un intero positivo\n");
        exit(-2);
    }
    
    sprintf(filepath,"%s/%s.txt",ROOT_PATH,argv[1]);
    if ((fd=open(filepath,O_RDONLY))<0){
        fprintf(stderr,"Errore apertura file\n");
        exit(-3);
    }
    close(fd);
    signal(SIGINT,handler);
    while(1){
        printf("Inserisci il giorno, mese, anno: ");
        scanf("%d%d%d",&gg,&mm,&aaaa);
        if (gg == -1 || mm == -1 || aaaa == -1)
			break;
		else if (gg < 0 || mm < 0 || aaaa < 0) {
			printf("errore: inserire interi positivi\n");
			continue;
		} else if (gg < 1 || gg > 31) {
			printf("errore: inserire <giorno> compreso tra 0 e 31\n");
			continue;
		} else if (mm < 1 || mm > 12) {
			printf("errore: inserire <mese> compreso tra 0 e 12\n");
			continue;
		}

        sprintf(date,"%02d/%02d/%04d",gg,mm,aaaa);

        if(pipe(p1p2)<0){
            perror("Errore pipe p1p2\n");
            exit(-4);
        }


        if((pid=fork())<0){
            perror("Errore fork1");
            exit(-5);
        }

        if(pid==0){
            signal(SIGINT,SIG_DFL);
            close(p1p2[0]);

            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep","grep",date,filepath,(char *)0);
            perror("Errore grep\n");
            exit(-6);
        }

        if(pipe(p2p3)<0){
            perror("Errore pipe p2p3\n");
            exit(-4);
        }

        if((pid=fork())<0){
            perror("Fork2");
            exit(-5);
        }

        if (pid==0){
            signal(SIGINT,SIG_DFL);

            close(p1p2[0]);
            close(p2p3[1]);

            close(0);
            dup(p1p2[1]);
            close(p1p2[1]);

            close(1);
            dup(p2p3[0]);
            close(p2p3[0]);

            execlp("sort","sort","-n",(char *)0);
            perror("Errore sort\n");
            exit(-6);
        }

        if((pid=fork())<0){
            perror("Fork3");
            exit(-5);
        }

        if(pid==0){
            signal(SIGINT,SIG_DFL);
            close(p1p2[0]);
            close(p1p2[1]);

            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);

            close(p2p3[1]);

            execlp("head","head","-n",argv[2],(char *)0);
            perror("Errore head");
            exit(-6);
        }
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p3[0]);
        close(p2p3[1]);

        wait(&status);
        wait(&status);
        wait(&status);
        counter++;
    }
    printf("Richieste servite: %d\n",counter);
    return 0;
}