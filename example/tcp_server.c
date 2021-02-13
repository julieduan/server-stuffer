#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 9903

int main(int argc, char *argv[])
{
    // Create a socket
    // AF_INET - Use IP
    // SOCK_STREAM - Use TCP
    // Third argument can specify a higher level protocol if desired
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Stops "port in use" error if the socket didn't close properly
    // By enabling the "re-use address" and "re-use port" options
    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Sets up the address to bind to
    struct sockaddr_in address;
    address.sin_family = AF_INET; // The address is an IP address
    address.sin_addr.s_addr = INADDR_ANY; // Listen for a connection *to* any IP address for this host
    address.sin_port = htons(PORT); // Listen on port 9903
    // The hton? family of functions convert numbers to a "network" byte order
    
    // Bind the server to the address
    bind(server_socket, (struct sockaddr *) &address, sizeof(address));
    
    // Server loop: Listen for new clients, with a queue of size 5
    listen(server_socket, 5);
    printf("Waiting for connections...\n");
    
    struct sockaddr_in client_address;
    socklen_t address_length = sizeof(struct sockaddr_in);
    int client_socket = accept(server_socket, (struct sockaddr *) &client_address, &address_length);
    
    printf("New client!\n");
    
    // Send a message to the client!
    char buff[256];
    int n = read(client_socket, buff, sizeof(buff)); 
    if(n == -1){
        return -1;
    }
    n = write(client_socket, buff, strlen(buff) + 1);
    if(n == -1){
        return -1;
    }
    
    close(client_socket);
    
    // Close the server socket
    close(server_socket);
    
    return 0;
}