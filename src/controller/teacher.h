#ifndef _TEACHER_H
#define _TEACHER_H

#include "../../struct/httplib.h"
#include <jsoncpp/json/json.h>
#include "../../struct/log.h"

#define TEACHER_LOG "../../../log/err_controller.log"

// 添加一个教师
void add_teacher(const httplib::Request& req, httplib::Response& res);


void get_teacher_name(const httplib::Request& req, httplib::Response& res); 


#endif // _TEACHER_H
