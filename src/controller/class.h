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

// 绑定班级和学号
void bind_class_base_and_student(const httplib::Request& req, httplib::Response& res);

// 通过班级编号查询班级的所有学生信息
void get_class_allinfo_by_class_id(const httplib::Request& req, httplib::Response& res);


/**
 * 课程相关
 */



#endif // !_CLASS_H_

