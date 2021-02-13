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
    // SOCK_DGRAM - Use UDP
    // Third argument can specify a higher level protocol if desired
    int the_socket = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Sets up the address to bind to
    struct sockaddr_in address;
    address.sin_family = AF_INET; // The address is an IP address
    address.sin_addr.s_addr = INADDR_ANY; // Listen for datagrams *to* any IP address for this host
    address.sin_port = htons(PORT); // Listen on port 9903
    // The hton? family of functions convert numbers to a "network" byte order
    
    // Bind the server to the address
    bind(the_socket, (struct sockaddr *) &address, sizeof(address));
    
    // Server loop: Wait for input messages, send output messages
    printf("Waiting for messages...\n");
    
    struct sockaddr_in client_address;
    socklen_t address_length = sizeof(struct sockaddr_in);

    // Get the buffer size
    char tmp[10];
    int bytes = recvfrom(the_socket, tmp, sizeof(tmp), MSG_WAITALL, (struct sockaddr *) &client_address, &address_length);

    tmp[bytes] = 0;

    int size;
    int check = sscanf(tmp, "%d", &size);

    if (check < 1) {
        exit(1);
    }

    printf("Reading %d bytes\n", size);

    // Receive a message from any client
    char buffer[10];
    bytes = recvfrom(the_socket, buffer, size, MSG_WAITALL, (struct sockaddr *) &client_address, &address_length);
    // MSG_WAITALL - Block until we receive something
    
    buffer[bytes] = 0;
    
    if(bytes > 3){
            int x = 1/0;
    }
    
    printf("New client! '%s'\n", buffer);
    
    // Send a message back to that client
    // sendto(the_socket, buffer, strlen(buffer) + 1, MSG_CONFIRM, (struct sockaddr *) &client_address, address_length);
    // MSG_CONFIRM - Needed by the link layer (layer 2; ethernet, etc.) to keep an ARP cache entry "alive", see the man pages
    
    // Close the socket
    close(the_socket);
    
    return 0;
}
