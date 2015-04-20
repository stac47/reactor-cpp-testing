#include <string>
#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include "ConnectionAcceptor.h"

void ConnectionAcceptor::operator()() {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *result, *rp;
    if (getaddrinfo(NULL, _port.c_str(), &hints, &result) != 0) {
        std::cout << "Error getting address info" << std::endl;
        return;
    }
    int sfd = 0;
    int optval = 1;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1) {
            continue;
        }
        if (setsockopt(sfd, SOL_SOCKET,
                       SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
            std::cout << "Error setting SO_REUSEADDR option" << std::endl;
        }
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
            std::cout << "Socket " << sfd << " bound to "
                      << rp->ai_addr << std::endl;
            break; //SUCCESS
        }
        close(sfd);
        std::cout << "Error when binding the socket." << std::endl;
        return;
    }
    if (listen(sfd, 5) == -1) {
        std::cout << "Error when listening" << std::endl;
        return;
    }
    freeaddrinfo(result);
    while (true) {
        int cfd = accept(sfd, NULL, NULL);
        if (cfd == -1) {
            std::cout << "Accept() failed" << std::endl;
        }
        else {
            std::cout << "Connection created" << std::endl;
            _trafficManager->registerEventHandler(cfd, nullptr);
        }
    }
}
