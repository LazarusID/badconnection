#include "server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>

int make_socket(uint16_t port) {
    int fd;
    struct sockaddr_in name;

    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    name.sin_family = AF_INET;
    name.sin_port = htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, (struct sockaddr *)&name, sizeof(name)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(fd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return fd;
}

void listener(int sock, void (*handler)(int)) {

    struct sockaddr_in client;
    socklen_t client_len;

    fd_set active_fd_set, read_fd_set;

    FD_ZERO(&active_fd_set);
    FD_SET(sock, &active_fd_set);

    read_fd_set = active_fd_set;
    if (select(FD_SETSIZE, &read_fd_set, 0, 0, 0)) {
        perror("select");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (FD_ISSET(i, &read_fd_set)) {
            accept(i, (struct sockaddr *)&client, &client_len);
        }
    }
}