//
// Created by archhh on 10/31/22.
//
#include "log/log.h"

int main() {
    Log::Instance()->init(1, "./log", ".log", 0);

//    LOG_ERROR("test");
    LOG_INFO("test info");

}