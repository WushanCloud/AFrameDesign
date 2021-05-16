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
    Json::Value value_r;
    Json::Value value_w;
    Json::FastWriter writer;
    Json::Reader reader;
    // 获取教师名字
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(TEACHER_LOG, "get_teacher_info_by_name req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    // 数据库介入
    Teacher teacher;
    map<string, string> info = teacher.get_info_by_name(value_r["teacher_name"].asString());
    if (info.empty()) {
        value_w["error"] = "用户不存在";
    }
    value_w["teacher_name"] = info["teacher_name"];
    value_w["teacher_number"] = info["teacher_number"];
    value_w["teacher_passwd"] = info["teacher_passwd"];
    value_w["result"] = "true";

    res.body = writer.write(value_w);
}

void get_teacher_info_by_number(const httplib::Request& req, httplib::Response& res){
    Json::Value value_r;
    Json::Value value_w;
    Json::FastWriter writer;
    Json::Reader reader;
    // 获取教师名字
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(TEACHER_LOG, "get_teacher_info_by_number req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    // 数据库介入
    Teacher teacher;
    map<string, string> info = teacher.get_info_by_number(value_r["teacher_number"].asString());
    if (info.empty()) {
        value_w["error"] = "用户不存在";
    }
    value_w["teacher_name"] = info["teacher_name"];
    value_w["teacher_number"] = info["teacher_number"];
    value_w["teacher_passwd"] = info["teacher_passwd"];
    value_w["result"] = "true";

    res.body = writer.write(value_w);
}

void delete_teacher(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取要删除的教师信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(TEACHER_LOG, "delete_teacher req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    
    string number = value_r["teacher_number"].asString();
    string name = value_r["teacher_name"].asString();

    Teacher teacher;
    ret = teacher.delete_teacher(number, name);
    if (ret == false) {
        value_w["result"] = "false";
    } else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void update_teacher_passwd(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取更新密码的教师信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(TEACHER_LOG, "update_teacher_passwd req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    
    Teacher teacher;
    ret = teacher.update_passwd(value_r["teacher_number"].asString());
    if (ret == false) {
        value_w["result"] = "false";
    } else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}
