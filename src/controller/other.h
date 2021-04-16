#ifndef _OTHER_H
#define _OTHER_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "../../struct/httplib.h"

#include "../service/user.h"

// 处理其他未知请求
void other(const httplib::Request& req, httplib::Response& res);

// 验证账号密码是否正确
// 0 正确 1 账号错误 2 密码错误
int check_user(const std::string& user_type, const std::string& user_number, const std::string & user_passwd);

// 判断登录页面
void get_pages(const httplib::Request& req, httplib::Response& res);

#endif // !_OTHER_H
