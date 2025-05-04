#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std; // namespace std

int main() {

    const int server_port = 5555; // Server port number

    int sock = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket with IPv4
    if (sock < 0) { // Check if the socket was created successfully
        perror("error creating socket");
    }

    struct sockaddr_in sin; // Create a sockaddr_in structure for the server address
    memset(&sin, 0, sizeof(sin)); // Zero out the structure
    sin.sin_family = AF_INET; // Set the address family to IPv4
    sin.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces
    sin.sin_port = htons(server_port); // Convert the port number from host byte order to network byte order

    // Bind the socket to the address
    // Check if the binding for the socket was successful
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) { 
        perror("error binding socket");
    }

    if (listen(sock, 5) < 0) { // Listen for incoming connections
        // Check if the listening for the socket was successful
        perror("error listening to a socket");
    }

    struct sockaddr_in client_sin; // Create a sockaddr_in structure for the client address
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len); // Accept a connection from a client

    if (client_sock < 0) { // Check if the connection for the client was successful
        perror("error accepting client");
    }

    char buffer[4096]; // Buffer to store the data received from the client - 4096 bytes
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0); // Receive the data from the client
    if (read_bytes == 0) { // Check if the connection was closed
    // connection is closed
    }
    else if (read_bytes < 0) { // Check if the data was received successfully
    // error
    }
    else { // Print to console the data received from the client
        cout << buffer;
    }

    // Send a response back to the client
    int sent_bytes = send(client_sock, buffer, read_bytes, 0);

    if (sent_bytes < 0) { // Check if the data was sent successfully
        perror("error sending to client");
    }

    close(client_sock); // Close the client socket
    close(sock); // Close the server socket


    return 0;
}