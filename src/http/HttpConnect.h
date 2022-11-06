//
// Created by archhh on 10/31/22.
//

#ifndef HALFSTARSERVER_HTTPCONNECT_H
#define HALFSTARSERVER_HTTPCONNECT_H

#include <arpa/inet.h>   // sockaddr_in
#include "HttpResponse.h"
class HttpConnect {
public:
    struct sockaddr_in addr() const;
    char * ip() const;
    int fd() const;
    int port() const;
    bool is_closed() const;

private:
    struct sockaddr_in addr_;
    bool is_closed_;
    int port_;
    int fd_;
    char *ip_;
    http_response response_;
};


#endif //HALFSTARSERVER_HTTPCONNECT_H
