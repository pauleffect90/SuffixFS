#include <stdio.h>
#include "suffix.h"
#include "memory.h"

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>


int main()
{
    printf("SFS ENTRY POINT\n");

//    WSADATA wsaData;
//    SOCKET ConnectSocket = INVALID_SOCKET;
//    struct addrinfo *result = NULL,
//        *ptr = NULL,
//        hints;
//    int iResult;
//    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
//    ZeroMemory( &hints, sizeof(hints) );
//    hints.ai_family = AF_UNSPEC;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//    iResult = getaddrinfo("127.0.0.1", "52000", &hints, &result);
//
//    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
//
//        // Create a SOCKET for connecting to server
//        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
//                               ptr->ai_protocol);
//        if (ConnectSocket == INVALID_SOCKET) {
//            printf("socket failed with error: %ld\n", WSAGetLastError());
//            WSACleanup();
//            return 1;
//        }
//
//        // Connect to server.
//        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//        if (iResult == SOCKET_ERROR) {
//            closesocket(ConnectSocket);
//            ConnectSocket = INVALID_SOCKET;
//            continue;
//        }
//        break;
//    }
//
//    char sendBuffer[5];
//
//    iResult = send( ConnectSocket, sendBuffer, 5, 0 );
//
//    iResult = shutdown(ConnectSocket, SD_SEND);
//    closesocket(ConnectSocket);
//    WSACleanup();

    uint8_t bitMap[512];
    memset(bitMap, 0xFF, 512);

    SUFFIX_Mount(bitMap);



    printf("SFS EXIT POINT\n");
    return 0;
}
