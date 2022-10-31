//
// Created by archhh on 10/30/22.
//


#include "buffer.h"
#include <string.h>
buffer::buffer(int buffer_size):
        buffer_(buffer_size),
        read_pos(0),
        write_pos(0)
        {}

size_t buffer::bytes_written() const {
    return write_pos;
}

size_t buffer::bytes_read() const {
    return read_pos;
}

char *buffer::read_begin() {
    return begin() + read_pos;
}

std::string buffer::retrieve_to_str() {
    std::string str(read_begin(), bytes_unread());
    retrieve_all();
    return str;
}

void buffer::retrieve_all() {
    bzero(&buffer_[0], buffer_.size());
    write_pos = 0;
    read_pos = 0;
}
void buffer::has_written(size_t len) {
    write_pos += len;
}
size_t buffer::space_remain() const {
    return buffer_size_ - write_pos;
}

size_t buffer::bytes_unread() const {
    return write_pos - read_pos;
}
char* buffer::begin() {
    return &*buffer_.begin();  // 等价于&buffer[0]
}

char * buffer::write_begin() {
    return begin() + write_pos;
}

RC buffer::resize(size_t len) {
    if (read_pos + buffer_size_ - write_pos < len) {
        buffer_.resize(write_pos + len - 1);
    } else {
        size_t unread = write_pos - read_pos;
        std::copy(buffer_.begin() + read_pos, buffer_.begin() + write_pos, buffer_.begin());
        read_pos = 0;
        write_pos = unread;
    }
    return RC::SUCCESS;
}
RC buffer::write(const char *data, size_t len) {
    assert(data);
    if (space_remain() < len) {
        resize(len);
    }
    std::copy(data, data + len, buffer_.begin() + write_pos);
    write_pos += len;
    return RC::SUCCESS;
}


