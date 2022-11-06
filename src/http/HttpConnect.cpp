//
// Created by archhh on 10/31/22.
//

#include "HttpConnect.h"
struct sockaddr_in  HttpConnect::addr() const {
    return addr_;
}

char *HttpConnect::ip () const {
    return ip_;
}

int HttpConnect::port() const {
    return port_;
}

int HttpConnect::fd() const {
    return fd_;
}

