import socket

HOST = '127.0.0.1'
PORT = 8080

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect((HOST, PORT))
    # client.sendall(b'AAAAAAAAAAAAAAAAAAAAAAA')
    while True:
        data = input("Escreva echo para enviar uma mensagem ou quit para sair:")
        data = data.strip().lower()
        if not data:
            break   

        if data == "quit":
            break

        if data == "echo":
            message = input("Insira uma mensagem (ou escreva quit para sair): ")
       
        client.sendall(message.encode())
        data = client.recv(1024).decode()
        print(f"Received from server: {data}")

