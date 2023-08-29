import socket
import sys

HOST = '127.0.0.1'  # Localhost
PORT = 8080

try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((HOST, PORT))
        server_socket.listen()
        print(f"Server listening on {HOST}:{PORT}")
        
        # Accept incoming connections
        connection, address = server_socket.accept()
        print(f"Connected by {address}")
        
        # Receive and send data
        while True:
            data = connection.recv(1024)
            if not data:
                break
            connection.sendall(data)
            
        # Close the connection
        connection.close()
except socket.error as e:
    print(f"Error occurred: {e}")
    sys.exit(1)
