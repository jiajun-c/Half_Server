//
// Created by archhh on 10/30/22.
//

#ifndef HALFSTARSERVER_BUFFER_H
#define HALFSTARSERVER_BUFFER_H
#include "../rc.h"
#include <unistd.h>
#include <vector>
#include <assert.h>


class buffer {
public:
    buffer(int buffer_size = BUFFER_SIZE_);
    size_t bytes_written() const; // 已经写入的数据位置
    size_t bytes_read() const;  // 已经被读取的位置
    size_t bytes_unread() const; // 写入但是还没有被读的数据
    size_t space_remain() const;  // 剩余的空间
    RC resize(size_t len);        // 在当前的write的位置后面增加长度为len的空间
    RC write(const char * data, size_t len);
    RC write(const void * data, size_t len);

    RC readfd(int fd, int *Errno);
    RC writefd(int fd, int *Errno);

private:
    std::vector<char>buffer_;
    size_t buffer_size_;
    size_t read_pos;
    size_t write_pos;
};

