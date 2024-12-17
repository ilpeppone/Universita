#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000  // Dimensione massima per N (10^6)

long long distanze[MAX_N];

void merge(long long arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    long long L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(long long arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int N, Q;
    fscanf(input, "%d %d", &N, &Q);

    for (int i = 0; i < N; i++) {
        int x, y, z;
        fscanf(input, "%d %d %d", &x, &y, &z);
        distanze[i] = (long long)x * x + (long long)y * y + (long long)z * z;
    }

    // Ordina le distanze utilizzando Mergesort
    mergeSort(distanze, 0, N - 1);

    for (int i = 0; i < Q; i++) {
        int r;
        fscanf(input, "%d", &r);
        long long r_quadrato = (long long)r * r;

        int left = 0, right = N;
        while (left < right) {
            int mid = (left + right) / 2;
            if (distanze[mid] <= r_quadrato) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        fprintf(output, "%d\n", left);
    }

    fclose(input);
    fclose(output);

    return 0;
}
