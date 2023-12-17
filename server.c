#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER 1024
#define PORT 8080

void handle_http_request(char *request, int new_socket)
{
  char method[8], path[1024], protocol[16];

  sscanf(request, "%s %s %s", method, path, protocol);

  if (strcmp(method, "GET") == 0 && strcmp(path, "/") == 0) {
    char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
    write(new_socket, response, strlen(response));
  } else {
    char response[] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nO-onii-chan??.";
    write(new_socket, response, strlen(response));
  }
}

int main()
{
  char buffer[MAX_BUFFER];

  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == 0) {
    perror("Kyaaa onii-chan!! Socket creation failed!");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Onii-chan, bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 10) < 0) {
    perror("Onii-chan!! Listen failed!");
    exit(EXIT_FAILURE);
  }

  while(1) {
    printf("\nHwello Onii-chan ^-^! Watashi waiting for a connection...\n");
    socklen_t addrlen = sizeof(address);
    int new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (new_socket < 0) {
      perror("Onii-chan, accept failed");
      exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, MAX_BUFFER);
    printf("%s\n",buffer);

    handle_http_request(buffer, new_socket);

    close(new_socket);
  }

  return 0;
}
