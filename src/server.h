#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdint.h>

int make_socket(uint16_t port);

void listener(int socket, void (*handler)(int));

#endif