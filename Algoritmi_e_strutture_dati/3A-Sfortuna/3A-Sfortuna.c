#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w;
} Edge;

typedef struct {
    int p;    
    int rank; 
} Node;

void swap(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

//  per ordinare i bordi per peso uso quicksort
int partition(Edge edges[], int low, int high) {
    int pivot = edges[high].w; // il pivot è l'ultimo elemento
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (edges[j].w < pivot) { // confronto col peso del pivot
            i++;
            swap(&edges[i], &edges[j]);
        }
    }
    swap(&edges[i + 1], &edges[high]); // riposiziono il pivot
    return i + 1;
}

void quicksort(Edge edges[], int low, int high) {
    if (low < high) {
        int pi = partition(edges, low, high); 
        quicksort(edges, low, pi - 1);        
        quicksort(edges, pi + 1, high);       
    }
}

// funzione per comparare i bordi in base al peso 
int compare(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->w - edgeB->w;
}

int FindSet(Node nodes[], int x) {
    if (x != nodes[x].p) {
        nodes[x].p = FindSet(nodes, nodes[x].p);
    }
    return nodes[x].p;
}

void Union(Node nodes[], int x, int y) {
    x = FindSet(nodes, x);
    y = FindSet(nodes, y);

    if (nodes[x].rank > nodes[y].rank) {
        nodes[y].p = x; // collego y a x
    } else {
        nodes[x].p = y; // collego x a y
        if (nodes[x].rank == nodes[y].rank) {
            nodes[y].rank++; // incremento il rank se i rank erano uguali
        }
    }
}

// trovo MST usando l'algoritmo di Kruskal
int kruskal(Edge edges[], int N, int M) {
    
    quicksort(edges, 0, M - 1);

    // inizializzo i nodi
    Node* nodes = (Node*)malloc(N * sizeof(Node));
    for (int i = 0; i < N; i++) {
        nodes[i].p = i;   // ogni nodo è inizialmente il proprio genitore
        nodes[i].rank = 0; // il rank iniziale è 0
    }

    int mst_weight = 0;
    int edges_used = 0;

    // riordino in bordi in ordine crescente
    for (int i = 0; i < M && edges_used < N - 1; i++) {
        int u = edges[i].u - 1; 
        int v = edges[i].v - 1;
        int w = edges[i].w;

        // se u e v appartengono a insiemi diversi, aggiungo il bordo al MST
        if (FindSet(nodes, u) != FindSet(nodes, v)) {
            Union(nodes, u, v);
            mst_weight += w;
            edges_used++;
        }
    }

    free(nodes);

    return mst_weight;
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Errore nell'aprire i file.\n");
        return 1;
    }

    int N, M;
    fscanf(inputFile, "%d %d", &N, &M);

    Edge* edges = (Edge*)malloc(M * sizeof(Edge));

    // leggo tutte le strade (bordi)
    for (int i = 0; i < M; i++) {
        fscanf(inputFile, "%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    // calcolo il costo min per collegare le città (MST)
    int mst_weight = kruskal(edges, N, M);

    fprintf(outputFile, "%d\n", mst_weight);

    fclose(inputFile);
    fclose(outputFile);
    free(edges);

    return 0;
}
