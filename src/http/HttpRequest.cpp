//
// Created by archhh on 10/31/22.
//

#include "HttpRequest.h"

void HttpRequest::init() {
    method_ = path_ = version_ = EMPTY;
    parseState = REQUEST_LINE;
    header_.clear();
    post_.clear();
}

RC HttpRequest::IsKeepAlive() const {
    if (header_.count("Connection") == 0) return RC::NOT_KEEP_ALIVE;
    if(header_.find("Connection")->second == "alive" && version_ == "1.1") return RC::SUCCESS;
}

RC HttpRequest::parse(buffer &buf) {
    if (buf.bytes_unread() <= 0) {
        return RC::GENERIC_ERROR;
    }
    RC rc;
    while (buf.bytes_unread() > 0 && parseState != FINISH) {
        char *end = std::search(buf.read_begin(), buf.write_begin(), CRLF, CRLF);
        std::string line(buf.read_begin(), end);
        switch (parseState) {
            case REQUEST_LINE:
                rc = ParseRequestLine(line);
                if (rc != RC::SUCCESS) {
                    return rc;
                }
                ParsePath();
                break;
            case HEADERS:
                rc = ParseHeader(line);
                if (rc != RC::SUCCESS) {
                    return rc;
                }
                if (buf.bytes_unread() < 2) {
                    parseState = FINISH;
                }
            case BODY:
                ParseBody(line);
                break;
            default:
                break;
        }
        if (end == buf.write_begin()) break;
        buf.retrive_until(end + 2);
    }
}

RC HttpRequest::ParseHeader(std::string &line) {
    std::regex patten("^([^:]*): ?(.*)$");
    std::smatch subMatch;
    if (regex_match(line, subMatch, patten)) {
        header_[subMatch[1]] = subMatch[2];
    } else {
        parseState = BODY;
    }
}

RC HttpRequest::ParsePath() {
    if (path_ == "/") path_ += ROOT_PAGE;
    if (DEFAULT_CATEGORY.count(path_)) {
        path_ += ".html";
    } else {
        LOG_ERROR("Invalid path");
        return RC::INVALID_PATH;
    }
    return RC::SUCCESS;
}

RC HttpRequest::ParseBody(std::string &line) {
    body_ = line;
    ParsePost(line);
    parseState = FINISH;
}

// void HttpRequest::ParsePost() {

// }