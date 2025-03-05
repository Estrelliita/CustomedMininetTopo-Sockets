#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int server_addrlen = sizeof(server_address);
    socklen_t client_addrlen = sizeof(client_address);
    char buffer[1024] = {0};
    char *confirmed = "Confirmed";

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    //printf("Server: Socket created successfully\n");

    // Set server address information
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    //printf("Server: Socket bound successfully\n");

    // Listen for incoming connections
    if (listen(server_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server: Listening on port %d\n", PORT);

    // Accept a connection (this will block)
    client_socket = accept(server_socket, (struct sockaddr *)&server_address, &client_addrlen);
    //printf("Server: Client connected\n");

    //print client IP and port
    printf("Client connected: IP: %s, Port: %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    //print client's message
    read(client_socket, buffer, 1024);
    printf("Client's message: %s\n", buffer);

    //Send message to client
    send(client_socket, confirmed, strlen(confirmed), 0);
    printf("Server: confirmed message sent\n");

    close(client_socket);
    close(server_socket);

    return 0;
}
