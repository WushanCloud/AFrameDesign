#pragma once 
#include <iostream>
#include <string>
#include <map>
#include "../../struct/db_connection.h"

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

	// 根据学生id获取学生的课程信息
	std::vector<std::string> get_class_by_id(const std::string& student_id);
};

class Teacher {
	DBconnect mysql;
public:
	// 根据老师编号获取老师的密码;
	std::string get_passwd_by_number(const std::string& student_number);

	// 根据老师编号获取老师信息
	std::map<std::string, std::string> get_info_by_number(const std::string& student_number);

	// 根据老师id获取老师的课程信息
	std::vector<std::string> get_class_by_id(const std::string& student_id);

    // 添加一位教师
    bool add_teacher(const std::string& teacher_number, const std::string& teacher_name, const std::string& teacher_passwd);
};

class Admin {
	DBconnect mysql;
public:
	// 根据账号获取管理员的密码;
	std::string get_passwd_by_number(const std::string& student_number);

    // 根据账号获取管理员名字
    std::string get_name_by_number(const std::string& admin_number);
};
