#include "student.h"

void get_student_name(const httplib::Request& req, httplib::Response& res) {
    Json::Value value;
    Json::FastWriter writer;
    
    // 从redis中查找
    // 获得key
    string redis_key = req.get_header_value("Cookie");
    Redis redis;
    string command = "hget " + redis_key + " student_name";
    redisReply* ret = redis.Command(command);
    if (ret->str == nullptr) {
        command = "hget " + redis_key + " student_number";
        redisReply* ret = redis.Command(command);
        // 数据库介入
        Student student;
        map<string, string> info = student.get_info_by_number(ret->str);
        string name = info["student_name"];
        command = "hset " + redis_key + " student_name " + name;
        redis.Command(command);
        value["admin_name"] = name.c_str();

        command = "hset " + redis_key + " student_id " + info["student_id"];
        redis.Command(command);
        command = "hset " + redis_key + " student_major " + info["student_major"];
        redis.Command(command);
        command = "hset " + redis_key + " student_class " + info["student_class"];
        redis.Command(command);
    } else {
        value["admin_name"] = ret->str;
    }

    res.body = writer.write(value);

}
    

