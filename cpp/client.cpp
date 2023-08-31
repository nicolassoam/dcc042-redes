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

int main(int argc, char** argv) {

    #ifdef _WIN32
        WSAData wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Winsock não iniciou." << std::endl;
            return -1;
        }
    #endif

    // Cria socket
    #ifdef _WIN32
        SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Erro ao criar socket" << std::endl;
            return -1;
        }
    #else
        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket < 0) {
            std::cerr << "Error creating socket" << std::endl;
            return -1;
        }
    #endif

    // Specify the server address and port
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); // Use the same port as the server
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Invalid address/Address not supported" << std::endl;
        return -1;
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return -1;
    }

    // Send data to the server
    while(true){
        char *message = new char[2040];
        
        for(int i = 1; i < argc; i++){
            strcat(message, argv[i]);
            strcat(message, " ");
        }
        
        ssize_t bytesSent = send(clientSocket, message, strlen(message), 0);
        if (bytesSent < 0) {
            std::cerr << "Error sending data" << std::endl;
            return -1;
        }

        // Receive the response from the server
        char buffer[1024];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead < 0) {
            std::cerr << "Error receiving data" << std::endl;
            return -1;
        }

        // Print the response
        std::cout << "Response from server: " << buffer << std::endl;
    }
    // Close the socket
    #ifdef _WIN32
        closesocket(clientSocket);
        WSACleanup();
    #else
        close(clientSocket);
    #endif
    return 0;
}
