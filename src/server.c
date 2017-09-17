#include "server.h"

#include <sys/socket.h>

int make_socket(uint16_t port) {
    int fd;
    fd = socket(PF_INET, SOCK_STREAM, 0);
    return fd;
}