#ifndef _OTHER_H
#define _OTHER_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "../../struct/httplib.h"

// 处理其他未知请求
void other(const httplib::Request& req, httplib::Response& res);

// 判断登录页面
void get_pages(const httplib::Request& req, httplib::Response& res);

#endif // !_OTHER_H
