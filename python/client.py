import socket

HOST = '127.0.0.1'
PORT = 8080

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect((HOST, PORT))
    # client.sendall(b'AAAAAAAAAAAAAAAAAAAAAAA')
    while True:
        data = input("Escolha um dos comandos a seguir: \n- Echo \n- Quit \n\n")
        data = data.strip().lower()
        if not data:
            break   

        if data == "quit":
            break

        if data == "echo":
            message = input("Insira uma mensagem: ")

        else:
            print("Comando inválido!\n")
            continue
       
        client.sendall(message.encode())
        data = client.recv(1024).decode()
        print(f"Received from server: {data}\n")

