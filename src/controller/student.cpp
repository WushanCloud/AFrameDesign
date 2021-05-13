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
    
void add_student(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取要插入的学生信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(STUDENT_LOG, "add_student req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string number = value_r["student_number"].asString();
    string name = value_r["student_name"].asString();
    string passwd = value_r["student_passwd"].asString();

    Student student;
    ret = student.add_student(number, name, passwd);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void get_student_info_by_name(const httplib::Request& req, httplib::Response& res)
{
    Json::Value value_r;
    Json::Value value_w;
    Json::FastWriter writer;
    Json::Reader reader;
    // 获取学生名字
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(STUDENT_LOG, "get_student_info_by_name req的json解析失败");
        res.body = writer.write(value_w);
        return;
    }
    // 数据库介入
    Student student;
    map<string, string> info = student.get_info_by_name(value_r["student_name"].asString());
    if (info.empty()) {
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    value_w["student_name"] = info["student_name"];
    value_w["student_number"] = info["student_number"];
    value_w["student_passwd"] = info["student_passwd"];
    value_w["result"] = "true";

    res.body = writer.write(value_w);
}

void get_student_info_by_number(const httplib::Request& req, httplib::Response& res)
{
    Json::Value value_r;
    Json::Value value_w;
    Json::FastWriter writer;
    Json::Reader reader;
    // 获取学生名字
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(STUDENT_LOG, "get_student_info_by_number req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    // 数据库介入
    Student student;
    map<string, string> info = student.get_info_by_number(value_r["student_number"].asString());
    if (info.empty()) {
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    value_w["student_name"] = info["student_name"];
    value_w["student_number"] = info["student_number"];
    value_w["student_passwd"] = info["student_passwd"];
    value_w["result"] = "true";

    res.body = writer.write(value_w);
}

void delete_student(const httplib::Request& req, httplib::Response& res)
{
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取要删除的学生信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(STUDENT_LOG, "delete_student req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string number = value_r["student_number"].asString();
    string name = value_r["student_name"].asString();

    Student student;
    ret = student.delete_student(number, name);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void update_student_passwd(const httplib::Request& req, httplib::Response& res)
{
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取更新密码的学生信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(STUDENT_LOG, "update_student_passwd req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    Student student;
    ret = student.update_passwd(value_r["student_number"].asString());
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}
