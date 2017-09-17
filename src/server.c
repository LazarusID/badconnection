#include "server.h"
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

int make_socket(uint16_t port) {
    int fd;
    struct sockaddr_in name;

    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        exit(EXIT_FAILURE);
    }

    name.sin_family = AF_INET;
    name.sin_port = htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(fd, (struct sockaddr *)&name, sizeof(name));

    return fd;
}