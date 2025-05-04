from socket import socket, AF_INET, SOCK_DGRAM # Import socket module and constants

s = socket(AF_INET, SOCK_DGRAM) # Create a UDP socket (SOCK_DGRAM) with IPv4 (AF_INET)

dst_ip = '127.0.0.1' # Destination IP address- localhost
dst_port = 12345 # Destination port number

s.sendto(b'Hello', (dst_ip,dst_port)) # Send a message to the server (127.0.0.1, 12345)

data, sender_info = s.recvfrom(2048) # Receive a response from the server (with buffer size 2048 bytes)
print(data.decode('utf-8')) # Decode the received data from bytes to string and print it
print(sender_info) # Print the sender's info (IP address and port number)

s.close() # Close the socket
