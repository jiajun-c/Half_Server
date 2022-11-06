#define PORT_ 3000
#define BUFFER_SIZE_ 2048
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#define kv std::unordered_map<std::string, std::string>
#define EMPTY ""
#define CRLF  "\r\n"
#define ROOT_PAGE ".index.html"
// 资源的前缀类型
const std::unordered_map<std::string, std::string> SUFFIX_TYPE = {
        {".html", "text/html"},
        {".pdf", "application/pdf"},
        { ".avi",   "video/x-msvideo" },
        { ".css",   "text/css "},
        { ".js",    "text/javascript "},
};

const std::unordered_map<int, std::string> STATUS_CODE = {
        {200, "OK"},
        {400, "Bad Request"},
        {403, "Forbidden"},
        {404, "NOT FOUND"}
};

const std::unordered_map<int, std::string> PATH_OF_CODE {
        {400, "./400.html"},
        {403, "./403.html"},
        {404, "./404.html"}
};

enum PARSE_STATE {
    REQUEST_LINE,   // 正在解析请求首行
    HEADERS,        // 正在解析header
    BODY,           // 正在解析主体
    FINISH,         // 解析完成
};

enum HTTP_CODE {
    NO_REQUEST = 0,
    GET_REQUEST,
    BAD_REQUEST,
    NO_RESOURSE,
    FORBIDDENT_REQUEST,
    FILE_REQUEST,
    INTERNAL_ERROR,
    CLOSED_CONNECTION,
};

// 文件的目录
const std::unordered_set<std::string> DEFAULT_CATEGORY{
        "/index", "/register", "/login",
        "/welcome", "/video", "/picture",
        };