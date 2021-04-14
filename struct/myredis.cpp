#include "myredis.h"

Redis::Redis(std::string address, int port) {
    this->address_ = address;
    this->port_ = port;
    this->redis_ = nullptr;
}

bool Redis::Connection() {
    this->redis_ = redisConnect(this->address_.c_str(), this->port_);
    if(this->redis_ != NULL && this->redis_->err)
    {
        printf("connection error: %s\n", this->redis_->errstr);
        return false;          
    }
    return true;
}

redisReply* Redis::Command(const std::string& command) {
    if (this->redis_ == nullptr) {
        if (!Connection()) {
            return nullptr;
        }
    }
    return (redisReply *)redisCommand(this->redis_, command.c_str());
}

void Redis::FreeReply(void* reply) {
    freeReplyObject(reply);
}

Redis::~Redis() {
    if (this->redis_ != nullptr) {
        redisFree(this->redis_);
    }
}
