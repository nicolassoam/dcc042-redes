import socket
import sys
import threading

HOST = '127.0.0.1'  # Localhost
PORT = 8080

def client_handle(connection, address):
    # Receive and send data
        while True:
            data = connection.recv(1024)
            if not data:
                break
            connection.sendall(data)
        # Close the connection
        connection.close()

try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((HOST, PORT))
        server_socket.listen()
        print(f"Server listening on {HOST}:{PORT}")
        
        # Accept incoming connections
        while True:
            connection, address = server_socket.accept()
            print(f"Connected by {address}")
            client_handler = threading.Thread(target=client_handle, args=(connection, address))
            client_handler.start()
        
except socket.error as e:
    print(f"Error occurred: {e}")
    sys.exit(1)
