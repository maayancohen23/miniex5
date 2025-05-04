import socket # Import socket module

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Create a TCP socket (SOCK_STREAM) with IPv4 (AF_INET)
dest_ip = '127.0.0.1' # Destination IP address- localhost
dest_port = 12345 # Destination port number
s.connect((dest_ip, dest_port)) # Connect to the server (127.0.0.1, 12345)

msg = input("Message to send: ") # Print a message to the user and get input
while not msg == 'quit': # Infinite loop to keep the client running and 
    #sending messages to the server until 'quit' is entered by the user
    s.send(bytes(msg, 'utf-8')) # Send the message to the server (encoded in utf-8)
    data = s.recv(4096) # Receive a response from the server (with buffer size 4096 bytes)
    print("Server sent: ", data.decode('utf-8')) # Decode the received data from bytes to string and print it
    msg = input("Message to send: ") # Get the next message from the user

s.close() # Close the socket