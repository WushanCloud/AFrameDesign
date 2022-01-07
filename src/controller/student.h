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

// 获取学生个人信息
void get_student_info(const httplib::Request& req, httplib::Response& res);

// 添加一个学生
void add_student(const httplib::Request& req, httplib::Response& res);

// 按学生姓名搜索学生
void get_student_info_by_name(const httplib::Request& req, httplib::Response& res);

// 按学生编号搜索学生
void get_student_info_by_number(const httplib::Request& req, httplib::Response& res);

// 删除一位学生
void delete_student(const httplib::Request& req, httplib::Response& res);

// 初始化一位学生的密码
void update_student_passwd(const httplib::Request& req, httplib::Response& res);

// 获取同班同学列表
void get_classmate(const httplib::Request& req, httplib::Response& res);

// 查找学生课程
void get_student_class(const httplib::Request& req, httplib::Response& res);

// 做作业
void add_student_work_answer(const httplib::Request& req, httplib::Response& res);

// 做实验
void add_student_test_answer(const httplib::Request& req, httplib::Response& res);

// 获得学生作业答案
void get_student_work_answer(const httplib::Request& req, httplib::Response& res);

// 获得学生实验答案
void get_student_test_answer(const httplib::Request& req, httplib::Response& res);
#endif // _STUDENT_H
