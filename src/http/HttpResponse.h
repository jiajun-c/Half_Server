//
// Created by archhh on 10/30/22.
//

#ifndef HALFSTARSERVER_HTTPRESPONSE_H
#define HALFSTARSERVER_HTTPRESPONSE_H
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>       // open
#include <unistd.h>      // close
#include <unordered_map>
#include <string>
#include "../log/log.h"
#include "../buffer/buffer.h"

class http_response {
public:
    http_response();
    ~http_response();
    RC make_response();
    int status_code() {return status_code_;}
    char *File() {return m_file_;}
    void UnmapFile();
private:
    RC add_status(buffer &buf); //添加状态代码
    RC add_header(buffer &buf);  // 添加头
    RC add_content(buffer &buf); // 添加传输内容
    void add_error(buffer &buf, std::string msg); // 出现错误的时候增加相关信息
    void make_response(buffer &buf);
    void handle_error();
    int status_code_;
    std::string path_;         // 请求的文件目录
    std::string src_dir;
    char* m_file_;  // 文件内存映射的指针
    struct stat m_fileStat_;    // 文件的状态信息
    bool keep_alive_;
    std::string get_file_type();
};

#endif //HALFSTARSERVER_HTTPRESPONSE_H
