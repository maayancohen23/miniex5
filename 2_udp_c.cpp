#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std; // namespace std

int main() {

    const char* ip_address = "127.0.0.1"; // Destination IP address- localhost (127.0.0.1)
    const int port_no = 5555; // Destination port number

    int sock = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket with IPv4
    if (sock < 0) { // Check if the socket was created successfully
        perror("error creating socket");
    }

    struct sockaddr_in sin; // Create a sockaddr_in structure for the destination address
    memset(&sin, 0, sizeof(sin)); // Zero out the structure
    sin.sin_family = AF_INET; // Set the address family to IPv4
    sin.sin_addr.s_addr = inet_addr(ip_address); // Convert the IP address from string to binary form
    sin.sin_port = htons(port_no); // Convert the port number from host byte order to network byte order

    //char data[] = "hello"; // Data that will be sent to the server
    // CHANGE: Recive data for sending to server from the user
    char data[1024];
    cout << "Enter message: ";
    cin.getline(data, sizeof(data));
    int data_len = sizeof(data); // len of the data that will be sent to the server

    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin)); // Send the data to the server
    if (sent_bytes < 0) { // Check if the data was sent successfully
        perror("error writing to socket");
    }

    struct sockaddr_in from; // Create a sockaddr_in structure for the source address
    unsigned int from_len = sizeof(struct sockaddr_in); 
    char buffer[4096]; // Buffer to store the data received from the server - 4096 bytes
    // Receive the data from the server
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len); 
    
    if (bytes < 0) { // Check if the data was received successfully
        perror("error reading from socket");
    }


    cout << "The server sent: " << buffer << endl; // Print to console the data received from the server

    close(sock); // Close the socket

    return 0;
}