#include "mocksystem.h"
#include "mock.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/select.h>

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

unsigned int sleep_return = UINT32_MAX;

int select_return = -1;
fd_set select_read_fdset;
fd_set select_write_fdset;
fd_set select_error_fdset;

int accept_return;
const char *accept_address;
uint16_t accept_port;
int accept_fd;

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

    sleep_return = 0;

    FD_ZERO(&select_read_fdset);
    FD_ZERO(&select_write_fdset);
    FD_ZERO(&select_error_fdset);

    int accept_return = -1;
    const char *accept_address = NULL;
    uint16_t accept_port = 0;
    int accept_fd = -1;
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

unsigned int sleep(unsigned int seconds) {
    mock_register_call_with(sleep, seconds);
    return sleep_return;
}

int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds,
           fd_set *restrict errorfds, struct timeval *restrict timeout) {

    mock_register_call(select);
    if (readfds)
        FD_COPY(readfds, &select_read_fdset);
    if (writefds)
        FD_COPY(writefds, &select_write_fdset);
    if (errorfds)
        FD_COPY(errorfds, &select_error_fdset);
    return select_return;
}

void select_will_return(int retval) { select_return = retval; }
fd_set *select_called_with_readfds(void) { return &select_read_fdset; }
fd_set *select_called_with_writefds(void) { return &select_write_fdset; }
fd_set *select_called_with_errorfds(void) { return &select_error_fdset; }

int accept(int socket, struct sockaddr *restrict address,
           socklen_t *restrict address_len) {

    accept_fd = socket;
    if (accept_address && address) {
        struct sockaddr_in *client = (struct sockaddr_in *)address;
        client->sin_addr.s_addr = inet_addr(accept_address);
        client->sin_port = htons(accept_port);
    }

    return accept_return;
}

void accept_will_return(int retval) { accept_return = retval; }
void accept_will_come_from_address(const char *ip) { accept_address = ip; }
void accept_will_come_from_port(uint16_t port) { accept_port = port; }
int accept_called_with_socket(void) { return accept_fd; }
