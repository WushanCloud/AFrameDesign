#pragma once 

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <openssl/md5.h>

/**
 * 生成Token令牌：
 * 生成规则：user_type + user_id + time(NULL);
 * 是否存入redis。
 */
class Token {
public:
    Token(const std::string user_type, const std::string user_id);
    
    bool SumMD5();

    std::string GetToken();

private:
    // 目标字符串：拟采用user_type + user_id
    std::string src_string;
    
    // 结果字符串：token
    std::string token;

};
