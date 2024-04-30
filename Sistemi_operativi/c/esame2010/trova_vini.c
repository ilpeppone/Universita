#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAX 20
#define N 256
void handler(int s){
    int status;
    wait(&status);
}
int main (int argc, char **argv){
    char vino[N],buff[N];
    int pid,pid1,pid2,ncantine,nread;
    int n1n2[2],n2pi[2],pip0[MAX][2];
    int i,j;
    signal(SIGINT,SIG_DFL);
    signal(SIGCHLD,handler);

    if (argc<2){
        printf("Uso: %s cantina-1 ... cantina-N\n",argv[0]);
        exit(1);
    }
    if (argv[1][0]!='/'){
        printf("Errore: non si tratta di un nome di file relativo\n");
        exit(2);
    }
    ncantine=argc-1;

    printf("Quale vino e' interessato a ricercare? 'fine' per terminare: \n");
    scanf("%s",vino);

    while(strcmp(vino,"fine")){
        for (i=0;i<ncantine;i++){
            if (pipe(pip0[i])<0){
                perror("Errore pipe");
                exit(3);
            }
        }
        if((pid=fork())<0){
            perror("Errore fork");
            exit(4);
        }
        if (pid==0){
            for(j=0;j<i;j++){
                close(pip0[j][0]);
            }

            if(pipe(n1n2)<0){
                perror("Error pipe 1");
                exit(5);
            }
            if(pipe(n2pi)<0){
                perror("Error pipe 2");
                exit(6);
            }
            if (pid1==fork()){
                perror("Errore fork nipote 1");
                exit(7);
            }
            if(pid1==0){
                close(pip0[i][0]);
                close(pip0[i][1]);

                close(n2pi[0]);
                close(n2pi[1]);

                close(1);
                dup(n1n2[1]);

                close(n1n2[1]);
                close(n1n2[0]);
                execlp("/usr/bin/grep","grep","disponibile",argv[1+i],(char *)0);
                perror("Grep 1");
                exit(8);
            }
            if(pid1>0){
                if((pid2=fork())<0){
                    perror("Errore fork nipote 2");
                    exit(9);
                }
                if(pid2==0){
                    /* Chiudo pipe usate solo dai due nipoti */
                    close(n1n2[0]);
                    close(n1n2[1]);
                    /* Ridirezione stdout verso il padre */
                    close(1);
                    dup(pip0[i][1]);
                    close(pip0[i][0]);
                    close(pip0[i][1]);
                    /* Redireziono lo stdin in lettura
						dal secondo nipote */
                    close(0);
                    dup(n2pi[0]);
                    close(n2pi[0]);
                    close(n2pi[1]);

                    //qui termina il figlio
                    execlp("/usr/bin/sort","sort","-n",(char*)0);
                    perror("Errore sort");
                    exit(10);
                }
            }
        }
        if (pid>0){
            //padre
            close(pip0[1][0]);
        }

        //mi metto in attesa delle risposte e le stampo a video
        for(i=0;i<ncantine;i++){
            printf("%s:\n",argv[i+1]);
            while((nread=read(pip0[i][0],buff,N-1))>0){
                write(1,buff,nread);
            }
            close(pip0[i][0]);
        }
        printf("Quale vino e' interessato a ricercare? 'fine' per terminare: \n");
        scanf("%s",vino);
    }
    return 0;
    
}