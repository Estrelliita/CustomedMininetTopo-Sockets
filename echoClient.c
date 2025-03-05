#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080  // Change this if your server uses a different port
#define BUFFER_SIZE 1024

int main(int argc, char const *argv){
  int client_socket = 0;
  struct sockaddr_in server_address, client_address;
  socklen_t client_addrlen = sizeof(client_address);
  char *server_ip = argv [1]; //Get server IP from command-line
  char buffer[1024] = {0};
  char *hello = "hello from client";

  //Create socket
  if((client_socket = socket(AF_INET, SOCK_STREAM, 0))<0){
    perror("error creating socket");
    return -1;
  }

  //Set server address info
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);

  if(inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0) {
    perror("Invalid address");
    return -1;
  }

  //Connect to server
  if(connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) <0){
    perror("Connection failed");
    return -1;
  }

  //Get and print client's IP and port
  if(getsockname(client_socket, (struct sockaddr *)&client_address, &client_addrlen) <0){
    perror("getsockname failed");
    return -1;
  }

  printf("Client's IP: %s, Port: %d\n", inet_ntoa(client_address.sin_addr), htons(client_address.sin_port));
  

  //Receive and print server's message
  int serverMes = read(client_socket, buffer, 1024);
  if(serverMes > 0){
    printf("Server: %s\n", buffer);

  }

  send(client_socket, hello, strlen(hello), 0);
  printf("Client: hello message sent\n");

  
  close (client_socket);
  return 0;

}
