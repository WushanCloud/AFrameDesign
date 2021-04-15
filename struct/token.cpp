#include "token.h"

Token::Token(const std::string user_type, const std::string user_id) {
    this->src_string.clear();
    this->src_string += user_type;
    this->src_string += user_id;
    this->src_string += std::to_string(time(NULL));
}

bool Token::SumMD5() {
    //1.定义MD5操作句柄&进行初始化
    MD5_CTX ctx;
    MD5_Init(&ctx);
    //2.计算MD5值
    int ret = MD5_Update(&ctx, this->src_string.c_str(), this->src_string.size());
    if(ret != 1) {
        return false;
    }
    //3.获取计算完成的MD5值
    unsigned char md5[16] = {0};
    ret = MD5_Final(md5, &ctx);
    if(ret != 1) {
        return false;
    }
    
    //32位的字符串就是计算出来的sessionid
    char tmp[2] = {0};
    char buf[32] = {0};
    for(int i = 0; i < 16; i++) {
        sprintf(tmp, "%02x", md5[i]);
        strncat(buf, tmp, 2);
    }

    token = buf;
    return true;
}

std::string Token::GetToken() {
    SumMD5();
    return this->token;
}

