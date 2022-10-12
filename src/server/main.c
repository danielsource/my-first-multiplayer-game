#include <netdb.h>
#include <stdio.h>

#include "util.h"

int
main(int argc, char **argv) {
    if (argc != 2)
        LOG_DIE("Usage: %s <server_address> <port>", argv[0]);

    struct sockaddr_in serv_addr = {0};
    int listen_fd, conn_fd, n;
    uint8_t buf[BUFSIZ], recv_line[BUFSIZ];

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        LOG_DIE("Socket error (%d)", listen_fd);

    return 0;
}

/* vim: set et sw=4 ts=4 tw=72: */
