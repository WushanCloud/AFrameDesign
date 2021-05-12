#include "student.h"

void get_student_name(const httplib::Request& req, httplib::Response& res) {
    Json::Value value;
    Json::FastWriter writer;
    value["user_name"] = "张三";
    res.body = writer.write(value);
    //res.set_content("张三", "text/plain");
}
    

