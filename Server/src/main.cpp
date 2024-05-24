#include <iostream>

#define DEFAULT_PORT 27015
#define DEFAULT_ADDRESS "127.0.0.1"

#ifdef _WIN64
#include <winsock2.h>

int main(int, char**){
    std::cout << "Media Server Open\n";

    //open server
    //windows socket data
    WSADATA wsaData;
    int wsaErr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaErr = WSAStartup(wVersionRequested, &wsaData);

    if(wsaErr != 0) {
        std::cout << "Winsock dll not found\n";
        return 1;
    } else {
        std::cout << wsaData.szSystemStatus << "\n";
    }

    //Create Socket
    SOCKET serverSocket;
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(serverSocket == INVALID_SOCKET) {
        std::cout << "Error opening socket.\n";
        WSACleanup();
        return 1;
    } else {
        std::cout << "Socket opened.\n";
    }

    //Bind Socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(DEFAULT_ADDRESS);//ip address
    service.sin_port = htons(DEFAULT_PORT);

    if (bind(serverSocket, reinterpret_cast<SOCKADDR*>(&service),
     sizeof(service)) == SOCKET_ERROR) {
        std::cout << "Failed to bind socket: " <<WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    } else {
        std::cout << "Socket bound successfully.\n";
    }

    //listen
    if(listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cout << "Socket listening error: " << WSAGetLastError() << "\n";
    } else {
        std::cout << "Waiting for connections...\n";
    }

    //accept connection
    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, nullptr, nullptr);

    if(acceptSocket == INVALID_SOCKET){
        std::cout << "Connection failure: " << WSAGetLastError() << "\n";
        WSACleanup();
        return -1;
    } else {
        std::cout << "Connection success.\n";
    }
    
    //recieve request
    char receiveBuffer[200];
    int rbyteCount = recv(acceptSocket, receiveBuffer, 200, 0);
    if(rbyteCount < 0) {
        std::cout << "In-buffer error: " << WSAGetLastError() << "\n";
        return 1;
    } else {
        std:: cout << "Data Recieved.\n";
    }

    //respond to request
    char buffer[200];
    std::cout << "Responding...\n";
    int sbyteCount = send(acceptSocket, buffer, 200, 0);
    if (sbyteCount == SOCKET_ERROR) {
        std::cout << "Response error: " << WSAGetLastError() << "\n";
    } else {
        std::cout << "Response successful\n";
    }
    

}

#elif __linux__
#include <sys/socket.h>

int main(int, char**){
    std::cout << "Media Server Open\n";

    //open server
    //code stub

    //respond to media request
}

#endif