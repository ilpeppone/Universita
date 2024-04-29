#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define DIM 100

static volatile sig_atomic_t count=0;

void handler_count(){
    printf("Numero di richieste servite : %d\n",count);
    exit(0);
}

void handler_start(){
    pritf("Handler avviato\n");
}

int main(int argc,char **argv){
    int pid,fd,nris,p1p2[2],pid1,pid2,status;
    char cognome[DIM], genere[DIM],path[200],nrisstr[DIM];

    if(argc != 2){
        printf("Uso: %s percorso dir\n");
        exit(1);
    }
    if(argv[1][0] != "/"){
        printf("Errore: %s non si tratta di un percorso assoluto\n",argv[1]);
        exit(2);
    }
    if((fd=open(argv[1], O_DIRECTORY))<0){
        perror("Errore nell'apertura della cartella\n");
        exit(3);
    }
    close (fd);

    signal(SIGINT,handler_count);

    while(1){
        printf("Inserire il cognome dell'autore di interesse, 'fine' per terminare:\n");
        scanf("%s",cognome);
        if(strcmp(cognome,"fine")==0){
            break;
        }
        sprintf(path,"%s/%s.txt",argv[1],genere);
        fd = open(path,O_RDONLY);
        if(fd<0){
            perror("open");
            continue;
        }
        close (fd);

        printf("Inserire il numero di risultati da visualizzare: \n");
        scanf("%d",&nris);

        if(nris <=0){
            printf("Errore: numero di risultati deve essere intero positivo");
            continue;
        }

        if (pipe(p1p2)<0){
            perror("pipe");
            exit(1);
        }
        
        pid1 = fork();
        if (pid1 <0 ){
            perror("fork");
            exit(1);
        }
        if (pid1 == 0){
            signal(SIGINT, SIG_DFL);
            signal(SIGUSR1,handler_start);

            pause();

            close(p1p2[0]);

            close(1);//chiusura stdout
            dup(p1p2[1]);//duplica p1p2 in 1 (ex stdout)
            close(p1p2[1]);
            //quando esegui execlp per saper il path 
            //del comando usa "which 'comando' " sul terminale
            execlp("/usr/bin/grep","grep",cognome,path, NULL);
            perror("execlp");
            exit(2);
        }
    pid2 = fork();
    if (pid2 < 0){
        perror("fork");
        exit(3);
    }
    if (pid2 == 0){
        signal(SIGINT, SIG_DFL);

        close(p1p2[1]);

        close(0);//chiusura stdin
        dup(p1p2[0]);
        close(p1p2[0]);

        sprintf(nrisstr,"%d",nris );
        execlp("/usr/bin/head","head","-n",nrisstr,NULL);
        perror("execlp");
        exit(4);
    }

    close(p1p2[0]);
    close(p1p2[1]);

    sleep(1);//invocare la kill dopo che p1 ha invocato la pause
    kill(pid1,SIGUSR1);

    wait(&status);
    wait(&status);

    count++;
    }
    printf("Numero di richieste servite: %d\n",count);
}