#define _POSIX_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>


int main(int argc,char **argv){
    int sd,err,n_localita;
    struct addrinfo hints,*ptr,*res;
    char regione[UINT16_MAX];

    if (argc!=3){
        fprintf(stderr,"Errore: uso -> ./bollettino_neve.c server porta\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGPIPE,SIG_IGN);

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;

    err=getaddrinfo(argv[1],argv[2],&hints,&res);
    if(err!=0){
        fprintf(stderr,"Errore risoluzione nome %s\n",gai_strerror(err));
        exit(EXIT_FAILURE);
    }
    
    /*connessione con fallback*/
    for(ptr=res;ptr!=NULL;ptr=ptr->ai_next){
        sd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        /*se la socket fallisce passa all'indirizzo successivo*/
        if(sd<0)
            continue;
            /*se la connessione va a buon fine esco dal ciclo*/
        if(connect(sd,ptr->ai_addr,ptr->ai_addrlen)==0)
            break;
        close(sd);
    }

    /*controllo che il client sia effettivamente connesso*/
    
    if(ptr==NULL){
        fprintf(stderr,"Errore di connessione");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);
    
    memset(regione, 0, sizeof(regione));
    fprintf(stdout, "Inserire 'regione', ['fine' per terminare]: ");
    if (fgets(regione, sizeof(regione), stdin) == NULL) {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

}