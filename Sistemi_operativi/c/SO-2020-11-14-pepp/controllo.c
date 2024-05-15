#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

#define DIM 16
#define BUFFDIM 256

static volatile sig_atomic_t byte_p2 = 0;

void handler(int s){
    printf("Byte letti dal processo P2: %d\n",byte_p2);
}

int main (int argc, char **argv){
    
    

    return 0;
}