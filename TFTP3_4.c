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
    // Creation of UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
    perror("Erreur lors de la création du socket");
    exit(EXIT_FAILURE);
}
	
    int e;
    struct addrinfo hints;
    struct addrinfo *res, *r;

    // Configuration of attributes of hint structures
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4 uniquement
    hints.ai_socktype = SOCK_DGRAM;  // Socket UDP
    hints.ai_protocol = IPPROTO_UDP;  // Protocole UDP

    // Resolution of the server's address
    e = getaddrinfo(argv[1], argv[3], &hints, &res);
    if (e != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(e));
        exit(EXIT_FAILURE);
    }

    // Configuration of server's address
    struct sockaddr_in server_addr;
    memcpy(&server_addr, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);

    // preparing the message to send
    char bufT[300] = "Message depuis le client UDP !";
    int msg_len = strlen(bufT);

    // send message via sendto()
    if (sendto(sockfd, bufT, msg_len, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erreur lors de l'envoi du message");
        exit(EXIT_FAILURE);
    }
	printf("Message envoyé au serveur %s sur le port %s.\n", argv[1], argv[3]);
	
    // browse and print every resolved address
    for (r = res; r != NULL; r = r->ai_next) {
        printf("Famille = %d, Type Socket = %d, Protocole = %d\n", 
               r->ai_family, r->ai_socktype, r->ai_protocol);
    }
    // freeing resources
	close(sockfd);
    freeaddrinfo(res); 
    exit(EXIT_SUCCESS);
    return 0;
}
