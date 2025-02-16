#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>     
#include <arpa/inet.h>      

#define PORT 65431          // Port to listen on
#define BUFFER_SIZE 1024    // Buffer size for receiving messages

// Define a structure 
typedef struct {
    int server_fd;
    struct sockaddr_in address;
    socklen_t addr_len;
} socket_info_t;

socket_info_t sock_info;  

void accept_new_connection(void);

int main() {
    int opt = 1;

    if ((sock_info.server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(sock_info.server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        close(sock_info.server_fd);
        exit(EXIT_FAILURE);
    }

    sock_info.address.sin_family = AF_INET;
    sock_info.address.sin_addr.s_addr = INADDR_ANY;
    sock_info.address.sin_port = htons(PORT);
    sock_info.addr_len = sizeof(sock_info.address);


    if (bind(sock_info.server_fd, (struct sockaddr *)&sock_info.address, sizeof(sock_info.address)) < 0) {
        perror("bind failed");
        close(sock_info.server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);


    accept_new_connection();


    close(sock_info.server_fd);
    return 0;
}

void accept_new_connection(void) {
    int new_socket;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_sent;

    if (listen(sock_info.server_fd, 5) < 0) {
        perror("listen failed");
        close(sock_info.server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) { 
        if ((new_socket = accept(sock_info.server_fd, (struct sockaddr *)&sock_info.address, &sock_info.addr_len)) < 0) {
            perror("accept failed");
            close(sock_info.server_fd);
            exit(EXIT_FAILURE);
        }

        printf("Connected to client: %s:%d\n", inet_ntoa(sock_info.address.sin_addr), ntohs(sock_info.address.sin_port));

        while (1) {
            memset(buffer, 0, BUFFER_SIZE); 

            bytes_read = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_read < 0) {
                perror("recv failed");
                break;
            } else if (bytes_read == 0) {
                printf("Client disconnected: %s:%d\n", inet_ntoa(sock_info.address.sin_addr), ntohs(sock_info.address.sin_port));
                break;
            }

            buffer[bytes_read] = '\0'; 
            printf("Received from client: %s\n", buffer);

            strncat(buffer, " Server reply", BUFFER_SIZE - bytes_read - 1);
            bytes_sent = send(new_socket, buffer, strlen(buffer), 0);
            if (bytes_sent < 0) {
                perror("send failed");
                break;
            }

            printf("Sent to client: %s\n", buffer);
        }

        close(new_socket);
    }
}