#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

static volatile sig_atomic_t counter = 0;
static volatile sig_atomic_t indice_figlio;
static volatile sig_atomic_t Nf;
static volatile sig_atomic_t flagTerminato = false;



void sigusr2_handler(int sig){
        (void) sig; // Ignora il parametro non utilizzato per evitare il warning
    counter--;
    printf("Child %d: Decrementare il contatore\n",indice_figlio);
    printf("Nuovo valore contatore child %d: %d\n",indice_figlio,counter);
}
void sigusr1_handler(int sig){
        (void) sig; // Ignora il parametro non utilizzato per evitare il warning
    counter++;
    printf("Child %d: Incrementare il contatore\n",indice_figlio);
    printf("Nuovo valore contatore child %d: %d\n",indice_figlio,counter);
}
void sigintchild(int sig){
        (void) sig; // Ignora il parametro non utilizzato per evitare il warning
    printf("Child %d:terminazione con valore counter %d\n",indice_figlio,counter);
    exit(0);
}

void sigintparent_handler(int sig){
        (void) sig; // Ignora il parametro non utilizzato per evitare il warning
    printf("Ricevuto CTRL-C --> attendo sincronizzazione con i children ...\n");
    int status;
    for (int i=0;i<Nf;i++){
        wait(&status);
    }
    printf("Tutti i file terminati, chiudo il programma\n");
    flagTerminato=true;
}

int main(int argc,char **argv){
    int Nf, *figlio,i;

    if (argc!=2){
        printf("Uso: ./figlicounterNf <Nf>\n");
        exit(1);
    }
 
    Nf=atoi(argv[1]);
    if (Nf<=0){
        fprintf(stderr,"Inserire un numero <Nf> maggiore di 0\n");
        exit(2);
    }
    figlio=(int *)malloc(Nf * sizeof(int));
    for (i=0;i<Nf;i++){
        int pid=fork();
        if (pid==0){
            indice_figlio=i;
            signal(SIGINT,sigintchild);
            signal(SIGUSR1,sigusr1_handler);
            signal(SIGUSR2,sigusr2_handler);
            while(1){
                /* Attraverso pause() il processo dorme in attesa di ricevere un segnale,
                una volta terminata l'esecuzione dell'handler corrispondente il processo tornera' in attesa
                di ricevere il prossimo segnale da gestire*/
                pause();
            }
        }else if(pid<0){
            printf("Errore nella fork child %d\n",i);
            exit(3);
        }
        //salvo i figli in un vettore
        figlio[i]=pid;
        
    }
    // Codice Parent: Gestore segnale SIGINT e genero casualmente segnale e child a cui mandarlo
    signal(SIGINT,sigintparent_handler);
    while(!flagTerminato){
        int random_index= rand() % Nf;
        int sig= ((rand() % 2) == 0 ? SIGUSR1 : SIGUSR2 );
        kill(figlio[random_index],sig);
        sleep(2);
    }
    free(figlio);
    return 0;
}