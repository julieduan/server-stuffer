#include "re-definition.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// AFL will provide data through this file which is inplace of a socket
// The file is created in the docker container
int entrance;
__attribute__((constructor))
static void open_entrance_file() {
  entrance = open("entrance", O_RDWR);
}

ssize_t real_recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {
  return ((real_recvfrom_t)dlsym(RTLD_NEXT, "recvfrom"))(sockfd, buf, len, flags, src_addr, addrlen);
}

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen){
  return read(entrance, buf, len);
}

ssize_t __recvfrom_chk(int sockfd, void *buf, size_t len, size_t buflen, int flags, struct sockaddr *src_addr, socklen_t *addrlen){
  return read(entrance, buf, len);
}

int real_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
  return ((real_accept_t)dlsym(RTLD_NEXT, "accept"))(sockfd, addr, addrlen);
}

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
  return entrance;
}

int real_listen(int sockfd, int backlog) {
  return ((real_listen_t)dlsym(RTLD_NEXT, "listen"))(sockfd, backlog);
}

int listen(int sockfd, int backlo){
  return 0;
}
