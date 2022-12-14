#ifndef BUFFER_H
#define BUFFER_H
#include "../rc.h"
#include <unistd.h>
#include <vector>
#include <assert.h>
#include <string>

class buffer {
public:
    buffer(int buffer_size = BUFFER_SIZE_);
    size_t bytes_written() const; // 已经写入的数据位置
    size_t bytes_read() const;  // 已经被读取的位置
    size_t bytes_unread() const; // 写入但是还没有被读的数据
    size_t space_remain() const;  // 剩余的空间
    RC resize(size_t len);        // 在当前的write的位置后面增加长度为len的空间
    RC write(const char *data);
    RC write(const char * data, size_t len);
    RC write(const void * data, size_t len);
    RC write(const std::string data);
    RC readfd(int fd, int *Errno);
    RC writefd(int fd, int *Errno);
    char * begin();
    char * write_begin();
    char * read_begin();
    void retrieve_all();
    // void buffer::retrive_until(const char* end);
    void retrive_until(const char *end);
    std::string retrieve_to_str();
    void has_written(size_t len);
private:
    std::vector<char>buffer_;
    size_t buffer_size_;
    size_t read_pos;
    size_t write_pos;
};

#endif //BUFFER_H
