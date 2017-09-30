#ifndef _MOCKSYSTEM_H_
#define _MOCKSYSTEM_H_

#include <stdint.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

void system_mock_init(void);

int socket(int domain, int type, int protocol);

void socket_will_return(int socket_id);
int socket_called_with_domain(void);
int socket_called_with_type(void);
int socket_called_with_protocol(void);

int bind(int socket, const struct sockaddr *address, socklen_t address_len);

void bind_will_return(int bind_value);
int bind_called_with_socket(void);
int bind_called_with_family(void);
uint16_t bind_called_with_port(void);
uint32_t bind_called_with_address(void);
socklen_t bind_called_with_len(void);

void perror(const char *s);

int listen(int fd, int backlog);
void listen_will_return(int retval);
int listen_called_with_socket(void);
int listen_called_with_backlog(void);

unsigned int sleep(unsigned int seconds);

int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds,
           fd_set *restrict errorfds, struct timeval *restrict timeout);
void select_will_return(int retval);
void select_will_set_readfd(int n, ...);
fd_set *select_called_with_readfds(void);
fd_set *select_called_with_writefds(void);
fd_set *select_called_with_errorfds(void);

int accept(int socket, struct sockaddr *restrict address,
           socklen_t *restrict address_len);
void accept_will_return(int retval);
void accept_will_come_from_address(const char *ip);
void accept_will_come_from_port(uint16_t);
int accept_called_with_socket(void);

int close(int fd);
void close_will_return(int retval);

#endif