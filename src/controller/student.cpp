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
        command = "hget " + redis_key + " user_number";
        redisReply* ret = redis.Command(command);
        // 数据库介入
        Student student;
        map<string, string> info = student.get_info_by_number(ret->str);
        string name = info["student_name"];
        command = "hset " + redis_key + " student_name " + name;
        redis.Command(command);
        value["student_name"] = name.c_str();


        command = "hdel " + redis_key + " user_number" + info["user_number"];
        redis.Command(command);
        command = "hset " + redis_key + " student_number " + info["student_number"];
        redis.Command(command);

        command = "hset " + redis_key + " student_id " + info["student_id"];
        redis.Command(command);
        command = "hset " + redis_key + " student_major " + info["student_major"];
        redis.Command(command);
        command = "hset " + redis_key + " student_class " + info["student_class"];
        redis.Command(command);
    } else {
        value["student_name"] = ret->str;
    }

    redis.FreeReply(ret);
    res.body = writer.write(value);
    cout << res.body << endl;
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

void get_student_info(const httplib::Request& req, httplib::Response& res) {
    Json::Value value;
    Json::FastWriter writer;
    
    // 从redis中查找
    // 获得key
    string redis_key = req.get_header_value("Cookie");
    Redis redis;
    string command;
    redisReply* ret;
    command = "hget " + redis_key + " student_number";
    ret = redis.Command(command);
    // 数据库介入
    Student student;
    map<string, string> info = student.get_info_by_number(ret->str);
    for (auto it = info.begin(); it != info.end(); it++) {
        value[it->first] = it->second;
    }
    res.body = writer.write(value);
    cout << res.body << endl;
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


void get_classmate(const httplib::Request& req, httplib::Response& res) {
    Json::Value value;
    Json::FastWriter writer;
    
    // 从redis中查找
    string redis_key = req.get_header_value("Cookie");
    Redis redis;
    string command = "hget " + redis_key + " student_major";
    redisReply* ret = redis.Command(command);
    string student_major = ret->str;
    command = "hget " + redis_key + " student_class";
    ret = redis.Command(command);
    string student_class = ret->str;

    if (student_major.empty() || student_class.empty()) {
        value["result"] = "false";
        res.body = writer.write(value);
        return;
    }

    ClassBase class_base;
    std::map<std::string, std::string> class_info = class_base.get_info_by_major_class(student_major, student_class);
    std::vector<std::string> numbers = class_base.get_all_student_number_by_id(class_info["class_base_id"]);

    Json::Value tmp_v;
    map<string, string> tmp_m;
    Student student;
    for (size_t i = 0; i < numbers.size(); i++) {
        tmp_v.clear();
        tmp_m =  student.get_info_by_number(numbers[i]);
        if (tmp_m.empty()){
            // 班级学生不存在
            continue;
        }
        tmp_v["student_number"] = numbers[i];
        tmp_v["student_name"] = tmp_m["student_name"];
        value.append(tmp_v);
    }
    res.body = writer.write(value);
    cout << res.body << endl;
}

void get_student_class(const httplib::Request& req, httplib::Response& res) {
    Json::Value value;
    Json::Value value_w;
    Json::FastWriter writer;
    
    // 从redis中查找
    string redis_key = req.get_header_value("Cookie");
    Redis redis;
    string command = "hget " + redis_key + " student_number";
    redisReply* ret = redis.Command(command);
    string student_number = ret->str;

    Class class_;
    vector<string> cla = class_.get_class_by_student_number(student_number);
    map<string, string> info;
    for (size_t i = 0; i < cla.size(); i++) {
        value.clear();
        info = class_.get_info_by_id(cla[i]);
        for (auto it = info.begin(); it != info.end(); it++) {
            value[it->first] = it->second;
        }
        value_w.append(value);
    }
    res.body = writer.write(value_w);
    cout << res.body << endl;

}

void add_student_work_answer(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(STUDENT_LOG, "add_student_work_answer req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string redis_key = req.get_header_value("Cookie");
    Redis redis;
    string command = "hget " + redis_key + " student_number";
    redisReply* rep = redis.Command(command);
    string student_number = rep->str;
    
    string answer = value_r["work_answer"].asString();
    string work_topic_id = value_r["work_topic_id"].asString();

    Student student;
    ret = student.add_student_work_answer(student_number, work_topic_id, answer);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void add_student_test_answer(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(STUDENT_LOG, "add_student_test_answer req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string redis_key = req.get_header_value("Cookie");
    Redis redis;
    string command = "hget " + redis_key + " student_number";
    redisReply* rep = redis.Command(command);
    string student_number = rep->str;
    
    string answer = value_r["test_answer"].asString();
    string test_topic_id = value_r["test_topic_id"].asString();

    Student student;
    ret = student.add_student_test_answer(student_number, test_topic_id, answer);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void get_student_work_answer(const httplib::Request& req, httplib::Response& res) {

}
