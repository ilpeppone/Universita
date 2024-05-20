#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define DD 200
#define Dim_Data 7
#define Dim_Tipo 50
#define DIM_PATH 250
static volatile sig_atomic_t counter;

void handler(){
    printf("Numero di richieste eseguite: %d",counter);
}

int main(int argc,char **argv){
    int fd,pid,p1p2[2],p0p2[2],status;
    char dir[DD],data[Dim_Data],tipo[Dim_Tipo],file_path[DIM_PATH];
    if(argc!=2){
        fprintf(stderr,"Uso: %s dir\n",argv[0]);
        exit(-1);
    }
    
    if(argv[1][0]=='/'){
        fprintf("Errore: %s non è il nome di un direttorio realativo\n",argv[1]);
        exit(-2);
    }

    sprintf(dir,"%s",argv[1]);

    if((fd=open(dir,O_DIRECTORY))<0){
        perror("Errore apertura cartella\n");
        exit(-3);
    }
    close(fd);
    
    signal(SIGINT,handler);

    while(1){
        printf("Inserisci il tipo di file da cercare\n");
        scanf("%s",tipo);

        printf("Inserisci la data di interesse\n");
        scanf("%s",data);

        sprintf(file_path,"%s/%s.txt",dir,data);

        if((fd=open(file_path,O_RDONLY))<0){
            perror("Errore apertura file\n");
            exit(-3);
        }
        close(fd);
        if(pipe(p1p2)<0){
            perror("Errore pipe p1p2\n");
            exit(-4);
        }
        if((pid=fork())<0){
            perror("Errore fork p1\n");
            exit(-5);
        }
        if(pid==0){
            signal(SIGINT,SIG_DFL);
            
            close(p1p2[0]);
            //redirezione stdout
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);
            execlp("grep","grep",tipo,(char *)0);
            perror("Errore grep\n");
            exit(-6);
        }
        if(pipe(p0p2)<0){
            perror("Errore p0p2\n");
            exit(-4);
        }
        if((pid=fork())<0){
            perror("Error fork p2");
            exit(-5);
        }
        if(pid==0){
            signal(SIGINT,SIG_DFL);

            close(p1p2[0]);
            //redirezione stdin
            close(0);
            dup(p1p2[1]);
            close(p1p2[1]);
            //redirezione stdout
            close(1);
            dup(p0p2[1]);
            close(p0p2[1]);
        }

        close(p1p2[1]);
        close(p0p2[0]);

        wait(&status);
        wait(&status);

        counter ++;
    }

}