#include <stdio.h>
#include <stdlib.h>
#define MAX 50
int main(){
    int i=0,dim,n_file_presenti,q_numero_richieste;
    FILE *input=fopen("input.txt","r");
    int vettore [MAX];
    if (input){
        while(!feof(input)){
            fscanf(input,"%d",&vettore[i]);
            i++;
        }
        dim=i;
        printf("%d\t",n_file_presenti=vettore[0]);
        printf("%d\n",q_numero_richieste=vettore[1]);
        printf("\nFine file\n");
    }else{
        printf("Errore: lettura del file errata.");
    }
    fclose("input.txt");

    return 0;
}