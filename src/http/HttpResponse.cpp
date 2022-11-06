//
// Created by archhh on 10/30/22.
//

#include "HttpResponse.h"

std::string http_response::get_file_type() {
    std::string text = "plain/text";
    std::string::size_type idx = path_.find_last_of('.');
    if (idx == std::string::npos) {
        return text;
    }
    std::string suffix = path_.substr(idx);
    if (SUFFIX_TYPE.count(suffix) != 1) return text;
    return SUFFIX_TYPE.find(suffix)->second;
}


RC http_response::add_header(buffer &buf) {
    std::string header;
    header += "Connection: ";
    if (keep_alive_) {
        header += "keep-alive\r\n";
        header += "keep-alive: max = 6, timeout = 220\r\n";
    } else {
        header += "close\r\n";
    }

    buf.write(header);
}

RC http_response::add_status(buffer &buf) {
    std::string status;
    if (STATUS_CODE.count(status_code_) != 1) return RC::STATUS_ERROR;
    status = STATUS_CODE.find(status_code_)->second;
    buf.write("HTTP/1.1 " + std::to_string(status_code_) + " " + status + "\r\n");
    return RC::SUCCESS;
}

RC http_response::add_content(buffer &buf) {
    int srcFd = open((src_dir + path_).data(), O_RDONLY);
    if (srcFd < 0) {
        LOG_ERROR("Failed to open the file: %s\n", (src_dir + path_).data());
        add_error(buf, "File Not Found!");
        return RC::FILE_NOT_FOUND;
    }
    int* mmRet = (int*)mmap(0, m_fileStat_.st_size, PROT_READ, MAP_PRIVATE, srcFd, 0);
    if(*mmRet == -1) {
        add_error(buf, "File NotFound!");
        return RC::FILE_NOT_FOUND;
    }
    m_file_ = (char*)mmRet;
    close(srcFd);
    return RC::SUCCESS;
}

void http_response::add_error(buffer &buf, std::string msg) {
    std::string body;
    std::string status = STATUS_CODE.find(status_code_)->second;
    body += "<html><title>Error</title> <body>";
    body += std::to_string(status_code_) + ":" + status + "\n";
    body += "<p>" + msg + "</p>";
    body += "<hr><em>HalfStarServer</em></body></html>";

    buf.write("Content-length: " + std::to_string(body.size()) + "\r\n\n");
    buf.write(body);
}

void http_response::handle_error() {
    if (PATH_OF_CODE.count(status_code_) == 1) {
        path_ = PATH_OF_CODE.find(status_code_)->second;
        stat((src_dir + path_).data(), &m_fileStat_);
    }
}

void http_response::make_response(buffer &buf) {
    bool error_code = 0;
    if (stat((src_dir + path_).data(), &m_fileStat_) < 0 || S_ISDIR(m_fileStat_.st_mode)) {
        status_code_ = 404;
        error_code = 1;
    } else if (!(m_fileStat_.st_mode & S_IROTH )) {
        status_code_ = 403;
        error_code = 1;
    } else {
        status_code_ = 200;
    }
    if (error_code) {
        handle_error();
    }
    add_status(buf);
    add_header(buf);
    add_content(buf);
}

void http_response::UnmapFile() {
    if (m_file_) {
        munmap(m_file_, m_fileStat_.st_size);
        m_file_ = nullptr;
    }
}