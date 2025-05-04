import socket # Import socket module

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a TCP socket (SOCK_STREAM) with IPv4 (AF_INET)
server_ip = 'localhost'  # Source IP address- localhost 
server_port = 12345 # Source port number
server.bind((server_ip, server_port)) # Bind the socket to the source IP and port
server.listen(5) # Listen for incoming connections (max 5 connections)

while True: # Infinite loop to keep the server running and listening for messages from clients
    client_socket, client_address = server.accept() # Accept a connection from a client
    print('Connection from: ', client_address) # Print the client's address (IP and port number)
    data = client_socket.recv(1024) # Receive a message from the client (with buffer size 1024 bytes)
    while not data.decode('utf-8') == '': # Infinite loop to keep the server running 
        #until an empty message is received (no more data)
        print('Received: ', data.decode('utf-8')) # Decode the received data from bytes to string and print it
        client_socket.send(data.upper()) # Send the received message back to the client (in uppercase)
        data = client_socket.recv(1024) # Receive the next message from the client (with buffer size 1024 bytes)

    print('Client disconnected') # Print that the client has disconnected
    client_socket.close() # Close the client socket