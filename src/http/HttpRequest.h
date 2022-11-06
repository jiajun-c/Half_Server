//
// Created by archhh on 10/31/22.
//

#ifndef HALFSTARSERVER_HTTPREQUEST_H
#define HALFSTARSERVER_HTTPREQUEST_H
#include "../buffer/buffer.h"
#include "../log/log.h"
#include <regex>
class HttpRequest {
public:
    void init();
    RC IsKeepAlive() const;
    RC parse(buffer &buf);
    std::string path() const;
    std::string method() const;
    std::string version() const;
private:
    std::string method_;
    std::string path_;
    std::string version_;
    std::string body_;
    kv header_; //使用键值对的方式
    kv post_;   // post请求表单
    PARSE_STATE parseState;
    RC ParsePath();
    RC ParseRequestLine(std::string &line);
    RC ParseBody(std::string &line);
    RC ParseHeader(std::string &line);
    RC ParsePost(std::string &line);
};


#endif //HALFSTARSERVER_HTTPREQUEST_H
