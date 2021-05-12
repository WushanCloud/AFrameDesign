#include "teacher.h"

void add_teacher(const httplib::Request& req, httplib::Response& res){
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取要插入的教师信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(TEACHER_LOG, "add_teacher req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    
    string number = value_r["teacher_number"].asString();
    string name = value_r["teacher_name"].asString();
    string passwd = value_r["teacher_passwd"].asString();

    Teacher teacher;
    ret = teacher.add_teacher(number, name, passwd);
    if (ret == false) {
        value_w["result"] = "false";
    } else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void get_teacher_name(const httplib::Request& req, httplib::Response& res) {
    Json::Value value;
    Json::FastWriter writer;
    
    // 从redis中查找
    // 获得key
    string redis_key = req.get_header_value("Cookie");
    Redis redis;
    string command = "hget " + redis_key + " teacher_name";
    redisReply* ret = redis.Command(command);
    if (ret->str == nullptr) {
        command = "hget " + redis_key + " teacher_number";
        redisReply* ret = redis.Command(command);
        // 数据库介入
        Teacher teacher;
        map<string, string> info = teacher.get_info_by_number(ret->str);
        string name = info["teahcer_name"];
        command = "hset " + redis_key + " teahcer_name " + name;
        redis.Command(command);
        value["admin_name"] = name.c_str();

        command = "hset " + redis_key + " teacher_id " + info["teacher_id"];
        redis.Command(command);
    } else {
        value["admin_name"] = ret->str;
    }

    res.body = writer.write(value);
}

void get_teacher_info_by_name(const httplib::Request& req, httplib::Response& res) {

}

void get_teacher_info_by_number(const httplib::Request& req, httplib::Response& res){

}
