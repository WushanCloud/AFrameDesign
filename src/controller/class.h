#ifndef _CLASS_H_
#define _CLASS_H_

#include "../../struct/httplib.h"
#include <jsoncpp/json/json.h>
#include <map>
#include "../../struct/log.h"
#include "../../struct/myredis.h"
#include "../service/user.h"

#define CLASS_LOG "../log/err_controller.log"

/**
 * 班级相关
 */

// 添加一个班级
void add_class_base(const httplib::Request& req, httplib::Response& res);

// 删除一位班级
void delete_class_base(const httplib::Request& req, httplib::Response& res);

// 通过班级专业和班级班号查班级信息
void get_class_base_by_major_class(const httplib::Request& req, httplib::Response& res);

// 通过班级编号查班级信息
void get_class_base_by_id(const httplib::Request& req, httplib::Response& res);

// 绑定班级和学号
void bind_class_base_and_student(const httplib::Request& req, httplib::Response& res);

// 通过班级编号查询班级的所有学生信息
void get_class_allinfo_by_class_id(const httplib::Request& req, httplib::Response& res);


/**
 * 课程相关
 */

// 创建一个课程
void add_class(const httplib::Request& req, httplib::Response& res);

// 通过课程名和课程专业查询课程
void get_class_by_name_and_major(const httplib::Request& req, httplib::Response& res);

// 通过课程编号查询课程
void get_class_by_class_id(const httplib::Request& req, httplib::Response& res);

// 通过课程编号查询授课教师
void get_teacher_by_class_id(const httplib::Request& req, httplib::Response& res);

// 通过课程编号删除课程
void delete_class_by_id(const httplib::Request& req, httplib::Response& res);

// 通过课程编号修改课程
void update_class_by_id(const httplib::Request& req, httplib::Response& res);

// 绑定学生和课程
void bind_class_and_student(const httplib::Request& req, httplib::Response& res);

// 通过课程编号查询所有学生
void get_all_student_by_class_id(const httplib::Request& req, httplib::Response& res);

// 绑定教师和课程
void bind_class_and_teacher(const httplib::Request& req, httplib::Response& res);

// 从课程删除学生
void delete_class_and_student(const httplib::Request& req, httplib::Response& res);

// 从课程删除教师
void delete_class_and_teacher(const httplib::Request& req, httplib::Response& res);
#endif // !_CLASS_H_

