#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <dlfcn.h>
#include <sys/types.h>

typedef ssize_t (*real_recvfrom_t)(int, void *, size_t, int, struct sockaddr *, socklen_t *);
typedef int (*real_accept_t)(int, struct sockaddr *, socklen_t *);
typedef int (*real_listen_t)(int sockfd, int backlog);
