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
    const int port_no = 5557; // Destination port number

    int sock = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket with IPv4
    if (sock < 0) { // Check if the socket was created successfully
        perror("error creating socket");
    }

    struct sockaddr_in sin; // Create a sockaddr_in structure for the destination address
    memset(&sin, 0, sizeof(sin)); // Zero out the structure
    sin.sin_family = AF_INET; // Set the address family to IPv4
    sin.sin_addr.s_addr = inet_addr(ip_address); // Convert the IP address from string to binary form
    sin.sin_port = htons(port_no); // Convert the port number from host byte order to network byte order
   
    // Connect to the server
    // Check if the connection for the server was successful
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) { 
        perror("error connecting to server");
    }

   // char data_addr[] = "Im a message"; // Data that will be sent to the server
   // CHANGE: Recive data for sending to server from the user
    char data_addr[1024];
    cout << "Enter message: ";
    cin.getline(data_addr, sizeof(data_addr));

    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0); // Send the data to the server

    if (sent_bytes < 0) { // Check if the data was sent successfulyy
    // error
    }

    char buffer[4096]; // Buffer to store the data received from the server - 4096 bytes
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0); // Receive the data from the server
    if (read_bytes == 0) { // Check if the connection was closed
    // connection is closed
    }
    else if (read_bytes < 0) { // Check if the data was received successfully
    // error
    }
    else { // Print to console the data received from the server
        cout << buffer;
    }

    close(sock); // Close the socket


    return 0;
}