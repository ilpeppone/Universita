#include <stdint.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "rxb.h" // Assumendo che `rxb.h` contenga la funzione `readline` o simile

#define BUFFER_SIZE 4096

// server  porta
// argv[0] argv[1]
int main(int argc, char *argv[])
{
	int sd, err;
	char *service;
	struct addrinfo hints, *res;

	/* Controllo argomenti */
	if (argc != 2) {
		fprintf(stderr, "Usage:\n\t%s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Per ripristinare un comportamento sensato delle socket */
	signal(SIGPIPE, SIG_IGN);

	service = argv[1];

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; /* IPv4 o IPv6 */
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	err = getaddrinfo(NULL, service, &hints, &res);
	if (err != 0) {
		fprintf(stderr, "Error: %s\n", gai_strerror(err));
		exit(EXIT_FAILURE);
	}

	sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	err = bind(sd, res->ai_addr, res->ai_addrlen);
	if (err < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	err = listen(sd, SOMAXCONN);
	if (err < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
    


	while (1) {
        rxb_t rxb;
	    int ns;
		char input[1024];
		size_t input_len;

		ns = accept(sd, NULL, NULL);
		if (ns < 0) {
			if (errno == EINTR)
				continue;
			perror("accept");
			exit(EXIT_FAILURE);
		}

		/* Alloco la memoria per il buffer rxb */
		rxb_init(&rxb, 64 * 1024);
    while(1){
		/* Inizializzo a zero il buffer per l'input */
		memset(input, 0, sizeof(input));
		input_len = sizeof(input)-1;

		/* Chiamo rxb_readline */
		err = rxb_readline(&rxb, ns, input, &input_len);
		if (err < 0) {
			perror("rxb_readline");
			exit(EXIT_FAILURE);
		}
        
        // Calcola la lunghezza dell'input e inviala al client
        int length = strlen(input);
        char length_str[10];
        snprintf(length_str, sizeof(length_str), "%d\n", length);
        write(ns, length_str, strlen(length_str));
        }

		rxb_destroy(&rxb);

		close(ns);
    
	}

	close(sd);

	return 0;
}
