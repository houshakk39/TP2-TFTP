#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <host> <file> <port>\n", argv[0]);
        return 1;
    }

    // Création du socket UDP
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    int e;
    struct addrinfo hints;
    struct addrinfo *res;

    // Configuration des attributs de la structure hints
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    // Résolution de l'adresse du serveur
    e = getaddrinfo(argv[1], argv[3], &hints, &res);
    if (e != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(e));
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    struct sockaddr_in server_addr;
    memcpy(&server_addr, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);

    // Préparation du message à envoyer
    // char bufT[300] = "Message depuis le client UDP !";
    char bufT[300] = "Message depuis le client UDP !";

    int msg_len = strlen(bufT);
    // preparation de la trame RRQ/WRQ 
    char bufTsended[309];

	bufTsended[0] = 0x00;  
	bufTsended[1] = 0x01;  

	memcpy(&bufTsended[2], bufT, msg_len);

	bufTsended[2 + msg_len] = 0x00;

	char mode[] = "octet";
	int mode_len = strlen(mode);
	memcpy(&bufTsended[3 + msg_len], mode, mode_len);

	bufTsended[3 + msg_len + mode_len] = 0x00;

	int bufTsended_len = 4 + msg_len + mode_len;

    
    // Envoi du message via sendto()
    if (sendto(sockfd, bufTsended, bufTsended_len, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erreur lors de l'envoi du message");
        exit(EXIT_FAILURE);
    }
// /home/ensea/Documents/TP2/serveur/zeros256 modèle (binaire) STL 3D | 256 bytes (256 bytes)
    printf("Message envoyé au serveur %s sur le port %s.\n", argv[1], argv[3]);

    // Fermeture propre du socket
    close(sockfd);

    return 0;
}
