#include <iostream>

#define DEFAULT_PORT 27015
#define DEFAULT_ADDRESS "127.0.0.1"

#ifdef _WIN64
#include <winsock2.h>

int main(int, char**){
    std::cout << "Media Client Open\n";

    //initialize
    WSADATA wsaData;
    int wsaErr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaErr = WSAStartup(wVersionRequested, &wsaData);

    if (wsaErr != 0) {
        std::cout << "Winsock dll not found" << std::endl;
        return 1;
    } else {
        std::cout << "The Winsock dll found" << std::endl;
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    }

    // Create a socket
    SOCKET clientSocket;
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    } else {
        std::cout << "Socket is OK!" << std::endl;
    }

    //Connect to Server
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(DEFAULT_ADDRESS);
    clientService.sin_port = htons(DEFAULT_PORT);

    if(connect(clientSocket, reinterpret_cast<SOCKADDR*>(&clientService), sizeof(clientService)) == SOCKET_ERROR){
        std::cout << "Connection failed: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    } else {
        std::cout << "Connection succesful.\n";
        std::cout << "Ready to send data...\n";
    }

    //request media
    char buffer[200];
    int sbyteCount = send(clientSocket, buffer, 200, 0);
    if (sbyteCount == SOCKET_ERROR) {
        std::cout << "Client send error: " << WSAGetLastError() << "/n";
        return -1;
    } else {
        std::cout << "Client sent request to server...\n";   
    }

    //recieve media
    char receiveBuffer[200];
    int rbyteCount = recv(clientSocket, receiveBuffer, 200, 0);
    if(rbyteCount < 0) {
        std::cout << "Error receiving data: " << WSAGetLastError() << "\n";
        return 1;
    } else {
        std::cout << "Client successfully received data.\n";
    }


    //confirm content with message

}

#elif __linux__
#include <sys/socket.h>

int main(int, char**){
    std::cout << "Media Client Open\n";

    //request media

    //recieve media

    //confirm content with message

}

#endif
