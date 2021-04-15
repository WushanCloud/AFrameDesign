#pragma once

#include <iostream>
#include <string>
#include <hiredis/hiredis.h>

/**
 * redisContext *redisConnect(const char *ip, int port);
 * void *redisCommand(redisContext *c, const char *format, ...);
 * void freeReplyObject(void *reply);
 * freeReplyObject(void *reply);
 */

class Redis {
public:
    Redis(std::string address = "127.0.0.1", int port = 6379);

    bool Connection();

    redisReply* Command(const std::string& command);

    void FreeReply(void* reply);

    ~Redis();

private:

    redisContext * redis_;

    std::string address_;

    int port_;
};
