#include <stdio.h>
#include <stdlib.h>
#define MAX 1000*1000


struct pair{
    int x;
    int id;
    
};
// Sottoprocedura di `merge_sort` per unire due range.  
void merge(int *arr, int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int i, j, left[n1], right[n2];

    for (i=0; i<n1; i++) {
        left[i] = arr[start+i];
    }

    for (j=0; j<n2; j++) {
        right[j] = arr[mid+1+j];
    }

    i = j = 0;


    for (int k=start; k<=end; k++) {
        if (i < n1) {
            if (j < n2) {
                arr[k] = (left[i]<= right[j]) ? left[i++] : right[j++];
            } else {
                arr[k] = left[i++];
            }
        } else {
            arr[k] = right[j++];
        }
    }
}

//Implementazione di `merge sort`.
void merge_sort(int *arr, int start, int end) {
    if (start < end) {
        int mid = start + (end-start) / 2;
        merge_sort(arr, start, mid);
        merge_sort(arr, mid+1, end);
        merge(arr, start, mid, end);
    }
}
struct pair find(){
    
}

void solve(struct pair *pairs,int pairs_size,int query,FILE *output){
    struct pair p = find(pairs,pairs_size,query); //Binary search da implementare
    if(p.x==query){
        fprintf(output,"%d",p.id);
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
        
        for(int j=0;j=s-1;j++){
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
    return -1;
    }
    escape_university(input,output);
    if(fclose(input)!=0 || fclose(output)!=0){
        return -2;
    }
    return 0;
}
