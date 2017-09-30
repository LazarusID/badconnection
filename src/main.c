#include <stdio.h>
#include <stdlib.h>

#include "brokenpipe.h"
#include "server.h"

int main(int argc, char **argv) {

    int sock = make_socket(7777);
    listener(sock, broken_pipe);

    return EXIT_FAILURE;
}