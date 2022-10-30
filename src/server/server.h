//
// Created by archhh on 10/30/22.
//

#ifndef HALFSTARSERVER_SERVER_H
#define HALFSTARSERVER_SERVER_H
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>


class server {
public:
private:
    uint32_t listen_event;
    uint32_t conn_event;
    int port_;
    int timeout_;
    int listen_fd_;
    bool is_closed;
    char *src;

};


#endif //HALFSTARSERVER_SERVER_H
