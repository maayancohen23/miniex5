from socket import socket, AF_INET, SOCK_DGRAM # Import socket module and constants

s = socket(AF_INET, SOCK_DGRAM) # Create a UDP socket (SOCK_DGRAM) with IPv4 (AF_INET)

src_ip = 'localhost' # Source IP address- localhost (127.0.0.1)
src_port = 12345 # Source port number
s.bind((src_ip, src_port)) # Bind the socket to the source IP and port

while True: # Infinite loop to keep the server running and listening for messages from clients
    data, sender_info = s.recvfrom(2048) # Receive a message from the client (with buffer size 2048 bytes)
    print(data.decode('utf-8')) # Decode the received data from bytes to string and print it
    print(sender_info) # Print the sender's info (IP address and port number)

    s.sendto(data.upper(), sender_info) # Send the received message back to the client (in uppercase)