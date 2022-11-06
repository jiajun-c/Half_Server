#include "config.h"
enum RC {
    SUCCESS = 0,
    GENERIC_ERROR, // 不知道返回什么就返回这个,乐
    STATUS_ERROR, // 找不到状态代码
    FILE_NOT_FOUND,
    NOT_KEEP_ALIVE,
    INVALID_PATH
};