#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

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
        std::cerr << "Error listening for connections" << std::endl;
        return -1;
    }

    std::cout << "Server listening on port 8080" << std::endl;

    // Accept incoming connections
    while(true){
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            std::cerr << "Error accepting connection" << std::endl;
            return -1;
        }

        std::cout << "Connected to client" << std::endl;

        // Receive and send data
        char buffer[1024];
        ssize_t bytesRead;
        while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
            send(clientSocket, buffer, bytesRead, 0);
        }

        if (bytesRead < 0) {
            std::cerr << "Error receiving data" << std::endl;
            return -1;
        }

        // Close the socket
    
        close(clientSocket);
    }
    close(serverSocket);

    return 0;
}