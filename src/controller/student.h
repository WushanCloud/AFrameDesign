#ifndef _STUDENT_H
#define _STUDENT_H

#include "../../struct/httplib.h"
#include <jsoncpp/json/json.h>
#include <map>
#include "../../struct/log.h"
#include "../../struct/myredis.h"
#include "../service/user.h"

#define STUDENT_LOG "../log/err_controller.log"

// 获取学生名字
void get_student_name(const httplib::Request& req, httplib::Response& res); 

// 添加一个学生
void add_teacher(const httplib::Request& req, httplib::Response& res);

#endif // _STUDENT_H
