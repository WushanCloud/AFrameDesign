#ifndef _TEACHER_H
#define _TEACHER_H

#include "../../struct/httplib.h"
#include <jsoncpp/json/json.h>
#include "../../struct/log.h"
#include <map>
#include "../../struct/myredis.h"
#include "../service/user.h"

#define TEACHER_LOG "../../../log/err_controller.log"

// 添加一个教师
void add_teacher(const httplib::Request& req, httplib::Response& res);

// 按教师姓名搜索教师
void get_teacher_info_by_name(const httplib::Request& req, httplib::Response& res);

// 按教师编号搜索教师
void get_teacher_info_by_number(const httplib::Request& req, httplib::Response& res);
#endif // _TEACHER_H
