import socket

HOST = '127.0.0.1'
PORT = 8080

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect((HOST, PORT))
    client.sendall(b'Hello, world')
    data = client.recv(1024).decode()
    print(f"Received from server: {data}")

