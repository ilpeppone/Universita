#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000*1000

struct pair {
    int x;
    int id;
};

void merge(struct pair *pairs, int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    struct pair left[n1], right[n2];

    for (int i = 0; i < n1; i++) {
        left[i] = pairs[start + i];
    }

    for (int j = 0; j < n2; j++) {
        right[j] = pairs[mid + 1 + j];
    }

    int i = 0, j = 0;

    for (int k = start; k <= end; k++) {
        if (i < n1 && (j >= n2 || left[i].x <= right[j].x)) {
            pairs[k] = left[i++];
        } else {
            pairs[k] = right[j++];
        }
    }
}

void merge_sort(struct pair *pairs, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        merge_sort(pairs, start, mid);
        merge_sort(pairs, mid + 1, end);
        merge(pairs, start, mid, end);
    }
}

struct pair find(struct pair *pairs, size_t pairs_size, int target) {
    if (pairs_size == 0 || pairs == NULL) {
        return (struct pair) {-1, -1};
    }

    int start = 0;
    int end = pairs_size - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (pairs[mid].x == target) {
            return pairs[mid];
        } else if (pairs[mid].x < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    return (struct pair) {-1, -1};
}

void solve(struct pair *pairs, int pairs_size, int query, FILE *out_file) {
    struct pair p = find(pairs, pairs_size, query);

    if (p.x == query) {
        fprintf(out_file, "%d ", p.id);
    } else {
        fprintf(out_file, "NULL ");
    }
}

void escape_university(FILE *in_file, FILE *out_file) {
    struct pair pairs[MAX_SIZE];
    int pairs_size = 0;

    int N, Q;
    if (fscanf(in_file, "%d %d", &N, &Q) != 2) {
        fprintf(stderr, "Errore durante la lettura di N e Q\n");
        exit(-2);
    }

    for (int i = 0; i < N; i++) {
        int id, s;
        if (fscanf(in_file, "%d %d", &id, &s) != 2) {
            fprintf(stderr, "Errore durante la lettura di id e s\n");
            exit(-3);
        }
        for (int j = 0; j < s-1; j++) {
            int x;
            int result = fscanf(in_file, "%d", &x);
            if (result != 1) {
                fprintf(stderr, "Errore durante la lettura di x\n");
                exit(-4);
            }
            pairs[pairs_size].id = id;
            pairs[pairs_size].x = x;
            pairs_size++;
        }
    }

    merge_sort(pairs, 0, pairs_size - 1);
    
    while (Q > 0) {
        int query;
        if (fscanf(in_file, "%d", &query) != 1) {
            fprintf(stderr, "Errore durante la lettura di query\n");
            exit(-1);
        }
        solve(pairs, pairs_size, query, out_file);

        Q--;
    }
}

int main(void) {
    FILE *in_file = fopen("input.txt", "r");
    FILE *out_file = fopen("output.txt", "w");

    if (in_file == NULL || out_file == NULL) {
        fprintf(stderr, "Errore durante l'apertura dei file\n");
        exit(-1);
    }

    escape_university(in_file, out_file);

    if (fclose(in_file) != 0 || fclose(out_file) != 0) {
        fprintf(stderr, "Errore durante la chiusura dei file\n");
        exit(-1);
    }

    return 0;
}
