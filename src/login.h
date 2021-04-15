#ifndef _LOGIN_H
#define _LOGIN_H

#include "controll.h"
#include "../struct/token.h"
#include "../struct/myredis.h"
#include <jsoncpp/json/json.h>

#define LOG_PATH "../log/function.log"
#define ERR_LOG_PATH "../log/err_function.log"

void GetFunction(const httplib::Request& req, httplib::Response& res);
void PutFunction(const httplib::Request& req, httplib::Response& res);
void PostFunction(const httplib::Request& req, httplib::Response& res);
void DeleteFunction(const httplib::Request& req, httplib::Response& res);

// 注册登录token
bool LoginToken(const httplib::Request& req, httplib::Response& res);
// 检查是否为登录用户
bool CheckToken(const httplib::Request& req, httplib::Response& res);

class login{
public:
    httplib::Server *server = new httplib::Server;
    
    void runaction();
    void action();
private:
    const std::string www = "./www";
};

#endif // _LOGIN_H
