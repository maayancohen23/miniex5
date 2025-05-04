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

    int sock = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket with IPv4
    if (sock < 0) { // Check if the socket was created successfully
        perror("error creating socket");
    }

    struct sockaddr_in sin; // Create a sockaddr_in structure for the server address

    memset(&sin, 0, sizeof(sin)); // Zero out the structure

    sin.sin_family = AF_INET; // Set the address family to IPv4
    sin.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces
    sin.sin_port = htons(server_port); // Convert the port number from host byte order to network byte order

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) { // Bind the socket to the address
        perror("error binding to socket");
    }

    struct sockaddr_in from; // Create a sockaddr_in structure for the source address
    unsigned int from_len = sizeof(struct sockaddr_in); 
    char buffer[4096]; // Buffer to store the data received from the client - 4096 bytes
    // Receive the data from the client
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) { // Check if the data was received successfully
        perror("error reading from socket");
    }

    cout << "The client sent: " << buffer << endl; // Print to console the data received from the client

    // Send a response back to the client
    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
    if (sent_bytes < 0) { // Check if the data was sent successfully
        perror("error writing to socket");
    }

    close(sock); // Close the socket

    return 0;
}