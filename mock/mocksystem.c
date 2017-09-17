#include "mocksystem.h"
#include "mock.h"
#include <netinet/in.h>
#include <stdlib.h>

int socket_domain = -1;
int socket_type = -1;
int socket_protocol = -1;
int socket_return = -1;

int bind_socket = -1;
int bind_family = -1;
uint16_t bind_port = 0;
uint32_t bind_address = 0;
socklen_t bind_len = 0;
int bind_return = -1;

int listen_return = -1;
int listen_socket = -1;
int listen_backlog = -1;

void system_mock_init(void) {
    socket_domain = -1;
    socket_type = -1;
    socket_protocol = -1;
    socket_return = -1;

    bind_socket = -1;
    bind_family = -1;
    bind_port = 0;
    bind_address = 0;
    bind_len = 0;
    bind_return = -1;

    listen_return = -1;
    listen_socket = -1;
    listen_backlog = -1;
}

int socket(int domain, int type, int protocol) {
    socket_domain = domain;
    socket_type = type;
    socket_protocol = protocol;

    mock_register_call(socket);

    return socket_return;
}

void socket_will_return(int socket_id) { socket_return = socket_id; }

int socket_called_with_domain(void) { return socket_domain; }

int socket_called_with_type(void) { return socket_type; }

int socket_called_with_protocol(void) { return socket_protocol; }

int bind(int socket, const struct sockaddr *address, socklen_t address_len) {
    const struct sockaddr_in *addr;

    bind_socket = socket;
    addr = (struct sockaddr_in *)address;
    bind_family = addr->sin_family;
    bind_port = addr->sin_port;
    bind_address = addr->sin_addr.s_addr;
    bind_len = address_len;

    mock_register_call(bind);

    return bind_return;
}

void bind_will_return(int bind_value) { bind_return = bind_value; }

int bind_called_with_socket(void) { return bind_socket; }

int bind_called_with_family(void) { return bind_family; }
uint16_t bind_called_with_port(void) { return bind_port; }

uint32_t bind_called_with_address(void) { return bind_address; }

socklen_t bind_called_with_len(void) { return bind_len; }

void perror(const char *s) { mock_register_call(perror); }

int listen(int fd, int backlog) {
    listen_socket = fd;
    listen_backlog = backlog;

    mock_register_call(listen);

    return listen_return;
}
void listen_will_return(int retval) { listen_return = retval; }
int listen_called_with_socket(void) { return listen_socket; }
int listen_called_with_backlog(void) { return listen_backlog; }