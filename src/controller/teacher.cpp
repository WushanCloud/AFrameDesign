#include "teacher.h"

void add_teacher(const httplib::Request& req, httplib::Response& res){
    Json::Value value_w;
    Json::FastWriter writer;
    Json::Value value_r;
    Json::Reader reader;
    
    // 解析req的信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(TEACHER_LOG, "add_teacher 函数，json解析失败");
    }
}
