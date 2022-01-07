#ifndef _TEACHER_H
#define _TEACHER_H

#include "../../struct/httplib.h"
#include <jsoncpp/json/json.h>
#include "../../struct/log.h"
#include <map>
#include "../../struct/myredis.h"
#include "../service/user.h"

#define TEACHER_LOG "../log/err_controller.log"

// 添加一个教师
void add_teacher(const httplib::Request& req, httplib::Response& res);

// 获取教师名字
void get_teacher_name(const httplib::Request& req, httplib::Response& res);

// 按教师姓名搜索教师
void get_teacher_info_by_name(const httplib::Request& req, httplib::Response& res);

// 按教师编号搜索教师
void get_teacher_info_by_number(const httplib::Request& req, httplib::Response& res);

// 删除一位教师
void delete_teacher(const httplib::Request& req, httplib::Response& res);

// 初始化一位教师的密码
void update_teacher_passwd(const httplib::Request& req, httplib::Response& res);


/**
 * 教师系统
 */

// 获取教师的所有授课
void get_teacher_class(const httplib::Request& req, httplib::Response& res);

// 创建作业
void add_class_work(const httplib::Request& req, httplib::Response& res);

// 创建实验
void add_class_test(const httplib::Request& req, httplib::Response& res);

// 通过课程编号查询作业
void get_class_work_by_class_id(const httplib::Request& req, httplib::Response& res);

// 通过课程编号查询实验
void get_class_test_by_class_id(const httplib::Request& req, httplib::Response& res);

// 通过作业编号获得作业
void get_class_work_by_class_work_id(const httplib::Request& req, httplib::Response& res);

// 通过实验编号获得实验
void get_class_test_by_class_test_id(const httplib::Request& req, httplib::Response& res);

// 添加作业题目信息
void add_class_work_title(const httplib::Request& req, httplib::Response& res);

// 添加实验题目信息
void add_class_test_title(const httplib::Request& req, httplib::Response& res);

// 通过作业编号获得作业题目
void get_work_topic_by_class_work_id(const httplib::Request& req, httplib::Response& res);

// 通过作业编号获得作业题目
void get_test_topic_by_class_test_id(const httplib::Request& req, httplib::Response& res);

#endif // _TEACHER_H
