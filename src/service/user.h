#pragma once 
#include <iostream>
#include <string>
#include <map>
#include "../../struct/db_connection.h"
#include "../../struct/log.h"

#define ERRDIR "../log/function.log"


void trim(std::string& s);

/**
 * 根据userID获取相应信息
 */

class Student {
	DBconnect mysql_db;
public:
	// 根据学号获取学生的student_密码;
	std::string get_passwd_by_number(const std::string& student_number);

	// 根据学号获取学生信息
	std::map<std::string, std::string> get_info_by_number(const std::string& student_number);

	// 根据学生名字获取学生信息
	std::map<std::string, std::string> get_info_by_name(const std::string& student_name);

	// 根据学生id获取学生的课程信息
	std::vector<std::string> get_class_by_id(const std::string& student_id);

	// 添加学生信息
	bool add_student(const std::string& student_number, const std::string& student_name, const std::string& student_passwd, const std::string& student_major = "", const std::string& student_class = "0");

	// 删除一位学生
	bool delete_student(const std::string& student_number, const std::string& student_name = "");

	// 初始化学生密码
	bool update_passwd(const std::string& student_number, const std::string& student_passwd = "123456");
};

class Teacher {
	DBconnect mysql;
public:
	// 根据老师编号获取老师的密码;
	std::string get_passwd_by_number(const std::string& teacher_number);

	// 根据老师编号获取老师信息
	std::map<std::string, std::string> get_info_by_number(const std::string& teacher_number);

	// 根据老师名字获取老师信息
	std::map<std::string, std::string> get_info_by_name(const std::string& teacher_name);

	// 根据老师id获取老师的课程信息
	std::vector<std::string> get_class_by_id(const std::string& teacher_id);

    // 添加一位教师
    bool add_teacher(const std::string& teacher_number, const std::string& teacher_name, const std::string& teacher_passwd);

    // 删除一位教师
    bool delete_teacher(const std::string& teacher_number, const std::string& teacher_name = "");

    // 初始化教师密码
    bool update_passwd(const std::string& teacher_number, const std::string& teacher_passwd = "123456");
};

class Admin {
	DBconnect mysql;
public:
	// 根据账号获取管理员的密码;
	std::string get_passwd_by_number(const std::string& admin_number);

    // 根据账号获取管理员名字
    std::string get_name_by_number(const std::string& admin_number);

    // 更新管理员密码
    bool update_passwd(const std::string& admin_number, const std::string& admin_passwd = "123456");
};

class ClassBase {
    DBconnect mysql;
public:
    // 添加一个班级
    bool add_class_base(const std::string& class_major, const std::string& class_class);

    // 绑定班级和学号
    bool add_class_student_base(const std::string& class_base_id, const std::string& student_number);

    // 删除一个班级
    bool delete_class_base(const std::string& class_id);

    // 通过班级专业和班级班号查班级信息
	std::map<std::string, std::string> get_info_by_major_class(const std::string& class_major, const std::string& class_class);

    // 通过班级编号查班级信息
	std::map<std::string, std::string> get_info_by_id(const std::string& class_base_id);

	// 根据班级编号查询班级的学生
	std::vector<std::string> get_all_student_number_by_id(const std::string& class_base_id);

};

/**
 * 课程类
 */
class Class {
    DBconnect mysql;
public:
    // 添加一个课程
    bool add_class(const std::string& class_name, const std::string& class_base_id, const std::string& class_major, const std::string& class_class, const std::string& class_info);

    // 通过课程名和课程专业查询课程
    std::vector<std::map<std::string, std::string>> get_class_by_name_major(const std::string& class_name, const std::string& class_major);

    // 通过课程编号查询课程
    std::map<std::string, std::string> get_info_by_id(const std::string& class_id);

    // 通过课程编号删除课程
    bool delete_class(const std::string& class_id);

    // 通过课程编号修改课程
    bool update_class(const std::string& class_id, const std::string& class_name, const std::string& class_base_id, const std::string& class_major, const std::string& class_class, const std::string& class_info);

    // 给课程添加教师
    bool add_teacher_class(const std::string& class_id, const std::string& teacher_number);

    // 给课程删除教师
    bool delete_teacher_class(const std::string& class_id, const std::string& teacher_number);

    // 通过课程id查询授课老师
    std::vector<std::map<std::string, std::string>> get_teacher_by_id(const std::string& class_id);

    // 通过课程id查询听课学生
    std::vector<std::map<std::string, std::string>> get_student_by_id(const std::string& class_id);

    // 给课程添加学生
    bool add_student_class(const std::string& class_id, const std::string& student_number);

    // 给课程删除学生
    bool delete_student_class(const std::string& class_id, const std::string& student_number);
};

/***
 * 作业类
 */

class Work {
    DBconnect mysql;
public:
    // 添加一次作业
    bool add_work(const std::string& class_id, const std::string& work_name, const std::string& work_sorce);

    // 添加一次实验
    bool add_test(const std::string& class_id, const std::string& work_name, const std::string& work_sorce);

    // 通过课程编号查询作业
    std::vector<std::map<std::string, std::string>> get_work_by_id(const std::string& class_id);

    // 通过课程编号查询实验
    std::vector<std::map<std::string, std::string>> get_test_by_id(const std::string& class_id);
};

