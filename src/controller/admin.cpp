#include "admin.h"

void get_admin_name(const httplib::Request& req, httplib::Response& res) {
    Json::Value value;
    Json::FastWriter writer;
    
    // 从redis中查找
    // 获得key
    string redis_key = req.get_header_value("Cookie");
    Redis redis;
    string command = "hget " + redis_key + " admin_name";
    redisReply* ret = redis.Command(command);
    if (ret->str == nullptr) {
        command = "hget " + redis_key + " user_number";
        redisReply* ret = redis.Command(command);
        // 数据库介入
        Admin admin;
        string name = admin.get_name_by_number(ret->str);
        command = "hset " + redis_key + " admin_name " + name;
        redis.Command(command);
        value["admin_name"] = name.c_str();
    } else {
        value["admin_name"] = ret->str;
    }

    res.body = writer.write(value);
}

void update_admin_passwd(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取要插入的班级信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(ADMIN_LOG, "update_admin_passwd req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    Admin admin;
    ret = admin.update_passwd(value_r["admin_number"].asString(), value_r["admin_passwd"].asString());
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}
