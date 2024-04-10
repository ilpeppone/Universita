#include <stdlib.h>
#include <stdio.h>
#define MAX 1000*1000


struct pair{
    int x;
    int id;    
};
// Sottoprocedura di `merge_sort` per unire due range.  
void merge(struct pair *pairs, int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int i, j;
    struct pair left[n1], right[n2];

    for (i=0; i<n1; i++) {
        left[i] =  pairs[start+i];
    }

    for (j=0; j<n2; j++) {
        right[j] = pairs[mid+1+j];
    }

    i = j = 0;


    for (int k=start; k<=end; k++) {
        if (i < n1) {
            if (j < n2) {
                pairs[k] = (left[i].x < right[j].x) ? left[i++] : right[j++];
            } else {
                pairs[k] = left[i++];
            }
        } else {
            pairs[k] = right[j++];
        }
    }
}

//Implementazione di `merge sort`.
void merge_sort(struct pair *pairs, int start, int end) {
    if (start < end) {
        int mid = start + (end-start) / 2;
        merge_sort(pairs, start, mid);
        merge_sort(pairs, mid+1, end);
        merge(pairs, start, mid, end);
    }
}

struct pair find(struct pair *pairs, int start, int end, int target) {
     if (start > end) {
        return (struct pair) {-1, -1}; // Restituisce una coppia con valori -1 se l'elemento non è stato trovato
    }

    int mid = start + (end - start) / 2;

    if (pairs[mid].x == target) {
        return pairs[mid];
    } else if (pairs[mid].x < target) {
        return find(pairs, mid + 1, end, target);
    } else {
        return find(pairs, start, mid - 1, target);
    }
}

void solve(struct pair *pairs,int pairs_size,int query,FILE *output){
    struct pair p = find(pairs,0,pairs_size-1,query); //Binary search da implementare
    // Se il risultato è stato trovato, lo stampo;
    // sennò stampo "NULL ".
    if(p.x==query){
        fprintf(output,"%d\t",p.id);
    }else{
        fprintf(output,"NULL");
    }
}

void escape_university(FILE *input,FILE *output){
    struct pair pairs[MAX];
    int pairs_size=0;

    int N, Q;
    fscanf(input,"%d %d",&N,&Q);//N (il numero dei file presenti nell’archivio)
    for(int i=0; i<N;i++){      //Q (il numero di richieste a cui rispondere)
        int id,s;
        fscanf(input,"%d %d",&id,&s);//prende id e numero di interi contenuti
        
        for(int j=0;j<s-1;j++){
            int x;
            fscanf(input,"%d",&x);//x sono gli interi che vengono presi
            
            pairs[pairs_size].x=x;   //
            pairs[pairs_size].id=id; //
            pairs_size++;

            }
        }


    merge_sort(pairs,0,pairs_size);

    for(int i=0;i<Q; i++){
        int query;
        fscanf(input,"%d",&query);
        solve(pairs,pairs_size,query,output);
    }
}

int main(void){
    FILE *input=fopen("input.txt","r");
    FILE *output=fopen("output.txt","w");
    if (input==NULL || output==NULL){
        exit(1);
    }
    escape_university(input,output);
    if(fclose(input)!=0 || fclose(output)!=0){
        exit(2);
    }
    return 0;
}
