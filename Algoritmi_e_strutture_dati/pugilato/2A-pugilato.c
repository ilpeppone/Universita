#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 1000000
#define INITIAL_CAPACITY 10 // capacità iniziale per i rivali

#define WHITE 0      // non ancora visitato
#define RED 1        // colore 1 (primo gruppo)
#define BLUE -1      // colore 2 (secondo gruppo)

typedef struct {
    int *data;       // array di rivali
    int size;        // numero attuale di rivali
    int capacity;    // capacità attuale dell'array
} List;

typedef struct {
    int *data;
    int testa;
    int coda;
    int capacita; // aggiunto per gestire la capacità della coda
} Queue;

void enqueue(Queue *queue, int item) {
    if (queue->coda < queue->capacita) { // controllo se la coda non è piena
        queue->data[queue->coda++] = item;
    }
}

int dequeue(Queue *queue) {
    if (queue->testa < queue->coda) { // controllo se ci sono elementi nella coda
        return queue->data[queue->testa++];
    }
    return -1; // valore di errore se la coda è vuota
}

int isEmpty(Queue *queue) {
    return queue->testa == queue->coda;
}

// funzione per creare una coda
Queue* createQueue(int capacita) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(capacita * sizeof(int));
    queue->testa = 0;
    queue->coda = 0;
    queue->capacita = capacita; // inizializzo la capacità
    return queue;
}

// funzione per aggiungere un arco alla lista di adiacenza
void aggiungi_arco(List *adj, int u, int v) {
    // controllo se è necessario aumentare la capacità
    if (adj[u].size >= adj[u].capacity) {
        adj[u].capacity *= 2; // raddoppio la capacità
        adj[u].data = (int *)realloc(adj[u].data, adj[u].capacity * sizeof(int));
        if (adj[u].data == NULL) { // controllo se realloc ha avuto successo
            fprintf(stderr, "errore nella reallocazione della memoria per u: %d\n", u);
            exit(1); // termino il programma in caso di errore
        }
    }
    adj[u].data[adj[u].size++] = v;

    // raddoppio la capacità per v se necessario
    if (adj[v].size >= adj[v].capacity) {
        adj[v].capacity *= 2;
        adj[v].data = (int *)realloc(adj[v].data, adj[v].capacity * sizeof(int));
        if (adj[v].data == NULL) { // controllo se realloc ha avuto successo
            fprintf(stderr, "errore nella reallocazione della memoria per v: %d\n", v);
            exit(1); // termino il programma in caso di errore
        }
    }
    adj[v].data[adj[v].size++] = u;
}

// bfs per verificare se il grafo è bipartito
int BreadthFirstSearch(List *adj, int start, int *colore) {
    Queue *queue = createQueue(MAXN);
    enqueue(queue, start);
    colore[start] = RED;

    while (!isEmpty(queue)) {
        int u = dequeue(queue); 

        // itero su tutti i vicini (rivali) del nodo u
        for (int i = 0; i < adj[u].size; i++) {
            int v = adj[u].data[i];

            // se il nodo vicino non è colorato assegno il colore opposto
            if (colore[v] == WHITE) {
                colore[v] = -colore[u];
                enqueue(queue, v); // enqueue
            }
            // se il nodo vicino ha lo stesso colore il grafo non è bipartito
            else if (colore[v] == colore[u]) {
                free(queue->data);
                free(queue);
                return 0; 
            }
        }
    }
    free(queue->data);
    free(queue);
    return 1;
}

int main() {
    int N, M;
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    // controllo se i file sono stati aperti correttamente
    if (input == NULL || output == NULL) {
        fprintf(stderr, "errore nell'aprire i file.\n");
        return 1;
    }

    fscanf(input, "%d %d", &N, &M);

    // assicuro che N e M siano validi
    if (N <= 0 || M < 0 || N > MAXN) {
        fprintf(stderr, "numero di nodi o archi non valido.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    // inizializzodelle liste di adiacenza
    List adj[N]; // utilizzo solo N pugili
    for (int i = 0; i < N; i++) {
        adj[i].data = (int *)malloc(INITIAL_CAPACITY * sizeof(int)); // alloco memoria per i rivali
        adj[i].size = 0; // nessun rivale inizialmente
        adj[i].capacity = INITIAL_CAPACITY; // capacità iniziale
    }

    // array per tracciare il colore dei nodi (pugili)
    int colore[N]; // cambio da MAXN a N
    for (int i = 0; i < N; i++) {
        colore[i] = WHITE; // nessun colore assegnato inizialmente
    }

    // leggo le rivalità e creo la lista di adiacenza
    for (int i = 0; i < M; i++) {
        int u, v;
        fscanf(input, "%d %d", &u, &v);

        // controllo se u e v sono validi
        if (u < 0 || u >= N || v < 0 || v >= N) {
            fprintf(stderr, "indici di rivali non validi: %d, %d\n", u, v);
            fclose(input);
            fclose(output);
            return 1;
        }

        aggiungi_arco(adj, u, v);
    }

    // verifico per tutte le componenti connesse
    for (int i = 0; i < N; i++) {
        if (colore[i] == WHITE) { // se il nodo non è stato visitato
            if (!BreadthFirstSearch(adj, i, colore)) {
                fprintf(output, "FALSE\n");
                fclose(input);
                fclose(output);
                return 0; // esco dal programma con risultato FALSE
            }
        }
    }

    // se il grafo è bipartito stampo TRUE
    fprintf(output, "TRUE\n");
    
    // deallocazione memoria
    for (int i = 0; i < N; i++) {
        free(adj[i].data);
    }

    fclose(input);
    fclose(output);
    return 0;
}
