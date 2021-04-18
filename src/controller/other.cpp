#ifndef _OTHER_CPP
#define _OTHER_CPP 

#include "other.h"

void other(const httplib::Request& req, httplib::Response& res) {
    if (req.path.substr(1) == "favicon.ico") {
        res.set_content("1", "text/plain");
        return;                            
    }
    res.set_content("hello", "text/plain");
}

int check_user(const std::string& user_type, const std::string& user_number, const std::string & user_passwd) {
    std::string check_passwd;
    if (user_type == "2") {
        Student student;
        check_passwd = student.get_passwd_by_number(user_number);
    } else if (user_type == "1") { // 教师
        Teacher teacher;
        check_passwd = teacher.get_passwd_by_number(user_number);
    } else if (user_type == "0") { // 管理员
        Admin admin;
        check_passwd = admin.get_passwd_by_number(user_number);
    } else {
        return 1;
    }
    if (check_passwd == "0" || check_passwd == "1") {
        return 1;   // 账户不存在，或sql出错
    }
    if (check_passwd == user_passwd) {
        return 0;   // 登陆成功
    }
    else {
        return 2;   // 密码错误
    }
}

void get_pages(const httplib::Request& req, httplib::Response& res) {
    std::cout << 1 << std::endl;
    int user_type = stoi(req.get_param_value("usertype"));
    if (user_type == 2) {
        res.set_redirect("index2.html");
    }
}
#endif // !_OTHER_CPP
