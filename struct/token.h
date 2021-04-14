#pragma once 

#include <iostream>
#include <string>
#include <ctime>


/**
 * 生成Token令牌：
 * 生成规则：user_type + user_id + time(NULL);
 * 是否存入redis。
 */
class Token {
public:
    
private:
    // 目标字符串：拟采用user_type + user_id
    std::string src_string;
    
    // 结果字符串：token
    std::string token;

};
