// perror
#include <stdio.h>

// setsockopt
#include <sys/socket.h>

// dlsym
#include <dlfcn.h>

int socket(int socket_family, int socket_type, int protocol) {
    int (*original_socket) (int, int, int) = dlsym(RTLD_NEXT, "socket");
    int found = original_socket(socket_family, socket_type, protocol);
    if (-1 == found) {
        return -1;
    }

    int opt = 1;
    int set = setsockopt(found, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
    if (-1 == set) {
        perror("setsockopt (ignoring)");
    }
    return found;
}
