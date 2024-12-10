#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int e;
    struct addrinfo hints;
    struct addrinfo *res;

    // Effacer la structure hints et définir les critères
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // Utilisation d'IPv4
    hints.ai_socktype = SOCK_DGRAM; // Protocole UDP
    hints.ai_protocol = IPPROTO_UDP;

}
