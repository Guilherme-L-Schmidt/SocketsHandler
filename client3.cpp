#include "sockets.hpp"
#include <iostream>

#define CLIENT_NAME "client3"

int main() {
    SocketHandler::openSocket(CLIENT_NAME);
    std::cout << "Socket open" << std::endl;

    SocketHandler::Message com {"\0", "\0", "\0"};

    while (1) {
        if (SocketHandler::listenClient(&com, (timeval){1,0}) == 0){
            printf("Server died\n");
            return -1;
        }
        
        if (com.send_to != "\0") {
            std::cout << "Received from " << com.sent_from << ": " << com.message << std::endl;

            com.send_to = "1";
            com.sent_from = "3";

            SocketHandler::sendMessage(SocketHandler::connection_socket, com);
            std::cout << "Sent (" << com.message << ") to " << com.send_to << std::endl;
            
            com = {"\0", "\0", "\0"};
        }
    }
}