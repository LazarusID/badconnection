#include "server.h"
#include <stdlib.h>
#include <sys/socket.h>

int make_socket(uint16_t port) {
    int fd;
    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        exit(EXIT_FAILURE);
    }
    return fd;
}