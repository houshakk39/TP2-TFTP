#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <host> <file> <port>\n", argv[0]);
        return 1;
    }

    int e;
    struct addrinfo hints;
    struct addrinfo *res, *r;

    // Configuration des attributs de la structure hints
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4 uniquement
    hints.ai_socktype = SOCK_DGRAM;  // Socket UDP
    hints.ai_protocol = IPPROTO_UDP;  // Protocole UDP

    // Résolution de l'adresse du serveur
    e = getaddrinfo(argv[1], "69", &hints, &res);
    if (e != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(e));
        exit(EXIT_FAILURE);
    }

    // Parcourir et afficher chaque adresse résolue
    for (r = res; r != NULL; r = r->ai_next) {
        printf("Famille = %d, Type Socket = %d, Protocole = %d\n", 
               r->ai_family, r->ai_socktype, r->ai_protocol);
    }

    freeaddrinfo(res); 
    exit(EXIT_SUCCESS);
}
