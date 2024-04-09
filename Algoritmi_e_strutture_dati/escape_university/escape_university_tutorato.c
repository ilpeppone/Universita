#include <stdio.h>
#include <stdlib.h>

void escape_university(FILE *input,FILE *output){
    int N, Q;
    fscanf(input,"%d %d",&N,&Q);
    for(int i=0; i<N;i++){
        int id,s;
        fscanf(input,"%d %d",&id,&s);
        for(int j=0;j=s-1;j++){
            int x;
            fscanf(input,"%d",&x);
            
            }
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
