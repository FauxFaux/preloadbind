// printf
#include <stdio.h>

// close
#include <unistd.h>

// AF_INET?
#include <sys/types.h>

// socket/bind
#include <sys/socket.h>

// sockaddr_in
#include <netinet/in.h>


int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == fd) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in serv_addr = {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(13337);

    int bound = bind(fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (-1 == bound) {
        perror("bind");
        close(fd);
        return 2;
    }

    int heard = listen(fd, 5);
    if (-1 == heard) {
        perror("listen");
        close(fd);
        return 3;
    }

    int accepted = accept(fd, NULL, NULL);
    if (-1 == accepted) {
        perror("accept");
        return 4;
    }

    int written = write(accepted, "hello\n", 6);
    if (6 != written) {
        if (-1 == written) {
            perror("write");
        }
        printf("warning: partial write\n");
    }


    if (-1 == close(accepted)) {
        perror("close client");
    }

    if (-1 == close(fd)) {
        perror("close server");
    }

    printf("spoke to a client; quitting\n");
}
