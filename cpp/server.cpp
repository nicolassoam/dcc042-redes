#include <iostream>
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <sys/types.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
#endif
#include <cstring>
#include <thread>



void client_handle(int socket_n){
        // Receive and send data
        char buffer[1024];
        ssize_t bytesRead;
        // while ((bytesRead = recv(socket_n, buffer, sizeof(buffer), 0)) > 0) {
        //     send(socket_n, buffer, bytesRead, 0);
        // }

        while(true){
            bytesRead = recv(socket_n, buffer, sizeof(buffer), 0);
            if(bytesRead == 0){
                break;
            } else if(bytesRead < 0){
                std::cerr << "Erro ao receber dados" << std::endl;
                break;
            } else {
                send(socket_n, buffer, bytesRead, 0);
            }
        }

        #ifdef _WIN32
            closesocket(socket_n);
        #else
            close(socket_n);
        #endif
}

int main() {

    #ifdef _WIN32
        WSAData wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Winsock não iniciou." << std::endl;
            return -1;
        }
    #endif

    // Cria socket
    #ifdef _WIN32
        SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Erro ao criar socket" << std::endl;
            return -1;
        }
    #else
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            std::cerr << "Erro ao criar socket" << std::endl;
            return -1;
        }
    #endif

    // Set up the server address and port
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080); // Use any available port

    // Bind the socket to the server address
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Erro ao tentar ouvir conexões" << std::endl;
        return -1;
    }

    std::cout << "Servidor no port 8080" << std::endl;

    // Accept incoming connections
    while(true){
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);

        #ifdef _WIN32
            SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
            if (clientSocket == INVALID_SOCKET) {
                std::cerr << "Erro ao aceitar conexões" << std::endl;
                return -1;
            }
        #else
            int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
            if (clientSocket < 0) {
                std::cerr << "Erro ao aceitar conexões" << std::endl;
                return -1;
            }
        #endif

        std::cout << "Conectado a client: " << clientAddress.sin_addr.s_addr << std::endl;
        std::thread client_thread(client_handle, clientSocket);
        client_thread.detach();

    }

    #ifdef _WIN32
        closesocket(serverSocket);
        WSACleanup();
    #else
        close(serverSocket);
    #endif

    return 0;
}