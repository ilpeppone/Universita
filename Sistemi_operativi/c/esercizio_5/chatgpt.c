#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static volatile sig_atomic_t counter = 0;
static volatile sig_atomic_t child_index;
static volatile sig_atomic_t nChildren;
static volatile sig_atomic_t flagTerminato = false;

void sigusr1_handler(int sig) {
    counter++;
    printf("Child %d: Incrementato il contatore\n", child_index);
    printf("Nuovo valore contatore child %d: %d\n", child_index, counter);
}

void sigusr2_handler(int sig) {
    counter--;
    printf("Child %d: Decrementato il contatore\n", child_index);
    printf("Nuovo valore contatore child %d: %d\n", child_index, counter);
}

void sigintchild(int sig) {
    printf("Child %d: Terminazione con valore counter %d\n", child_index, counter);
    exit(0);
}

void sigintparenthandler(int sig) {
    printf("Ricevuto CTRL-C --> Attendo sincronizzazione con i children...\n");
    int status;
    for (int i = 0; i < nChildren; i++) {
        wait(&status);
    }

    printf("Tutti i children terminati, chiudo il programma\n");
    flagTerminato = true;
}

int main(int argc, char *argv[]) {
    // Definisco handler dei segnali e vettore dove salvare pid children
    int *children;

    //Controllo parametri
    if (argc != 2) {
        fprintf(stderr, "Uso corretto: ./%s <nChildren>\n", argv[0]);
        exit(1);
    }
    if (atoi(argv[1]) <= 0) {
        fprintf(stderr, "Ci deve essere almeno un child da poter generare\n");
        exit(2);
    }

    nChildren = atoi(argv[1]);
    children = (int *)malloc(nChildren * sizeof(int));

    // Creo processi children pari a quanti inseriti dall'utente nel parametro
    for (int i = 0; i < nChildren; i++) {
        int pid = fork();
        if (pid == 0) {
            // Child process
            child_index = i;

            signal(SIGINT, sigintchild);
            signal(SIGUSR1, sigusr1_handler);
            signal(SIGUSR2, sigusr2_handler);

            while (1) {
                /* Attraverso pause() il processo dorme in attesa di ricevere un segnale,
                una volta terminata l'esecuzione dell'handler corrispondente il processo tornera' in attesa
                di ricevere il prossimo segnale da gestire*/
                pause();
            }
        } else if (pid < 0) {
            printf("Error nella fork child %d\n", i);
            exit(3);
        }

        //Salvo tutti i children in un vettore per poi poterli selezionare casualmente
        children[i] = pid;
    }

    // Codice Parent: Gestore segnale SIGINT e genero casualmente segnale e child a cui mandarlo
    signal(SIGINT, sigintparenthandler);

    while (!flagTerminato) {
        int random_index = rand() % nChildren;
        int sig = ((rand() % 2) == 0 ? SIGUSR1 : SIGUSR2);
        kill(children[random_index], sig);
        sleep(2);
    }

    free(children);

    return 0;
}
