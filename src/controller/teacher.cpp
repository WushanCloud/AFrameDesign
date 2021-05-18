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
    
    cout << "start" << endl;
    // 从redis中查找
    // 获得key
    string redis_key = req.get_header_value("Cookie");
    Redis redis;
    string command = "hget " + redis_key + " teacher_name";
    LOG(TEACHER_LOG, command);
    redisReply* ret = redis.Command(command);
    if (ret->str == nullptr) {
        command = "hget " + redis_key + " user_number";
        ret = redis.Command(command);
        // 数据库介入
        Teacher teacher;
        map<string, string> info = teacher.get_info_by_number(ret->str);
        string name = info["teacher_name"];
        command = "hset " + redis_key + " teacher_name " + name;
        redis.Command(command);
        value["teacher_name"] = name.c_str();

        command = "hset " + redis_key + " teacher_id " + info["teacher_id"];
        redis.Command(command);
        command = "hdel " + redis_key + " user_number " + ret->str;
        redis.Command(command);
        command = "hset " + redis_key + " teacher_number " + info["teacher_number"];
        redis.Command(command);
    } else {
        value["teacher_name"] = ret->str;
    }
    redis.FreeReply(ret);

    cout <<"end" << endl;
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


/**
 * 教师系统
 */

void get_teacher_class(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取登录的Cookie信息
    string redis_key = req.get_header_value("Cookie");
    Redis redis;

    // 获得登录教师编号
    string command = "hget " + redis_key + " teacher_number";
    redisReply * ret = redis.Command(command);
    string teacher_number = ret->str;
    LOG(TEACHER_LOG, teacher_number);

    Teacher teacher;
    Class class_;
    vector<string> class_ids = teacher.get_class_by_id(teacher_number);
    if (class_ids.empty()) {
        cout << "课程为空" << endl;
        return ;
    }

    Json::Value value;
    map<string,string> tmp_m;
    for (size_t i = 0; i < class_ids.size(); i++) {
        tmp_m.clear();
        value.clear();
        tmp_m = class_.get_info_by_id(class_ids[i]);
        if (tmp_m.empty()) {
            cout << class_ids[i] << endl;
            continue;
        }
        for (auto it = tmp_m.begin(); it != tmp_m.end(); it ++) {
            value[it->first] = it->second;
        }
        value_w.append(value);
    }
    res.body = writer.write(value_w);
    cout << res.body << endl;
    cout << "end" << endl;
}

void add_class_work(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;
    
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(TEACHER_LOG, "add_class_work req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string class_id = value_r["class_id"].asString();
    string work_name = value_r["work_name"].asString();
    string work_sorce = value_r["work_sorce"].asString();

    Work work;
    ret = work.add_work(class_id, work_sorce, work_sorce);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
    cout << res.body << endl;
}

void add_class_test(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;
    
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(TEACHER_LOG, "add_class_test req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string class_id = value_r["class_id"].asString();
    string test_name = value_r["test_name"].asString();
    string test_sorce = value_r["test_sorce"].asString();

    Work work;
    ret = work.add_test(class_id,test_name,test_sorce);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
    cout << res.body << endl;
}

void get_class_work_by_class_id(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(TEACHER_LOG, "get_class_work_by_class_id req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    
    Work work;
    vector<map<string,string>> info;
    info = work.get_work_by_id(value_r["class_id"].asString());
    if (info.empty()) {
        value_w["result"] = "false";
        value_w["error"] = "null";
        res.body = writer.write(value_w);
        return;
    }

    Json::Value value;
    for (size_t i = 0; i < info.size(); i++) {
        value.clear();
        for (auto it = info[i].begin(); it != info[i].end(); it++) {
            value[it->first] = it->second;
        }
        value_w.append(value);
    }
    res.body = writer.write(value_w);
    cout << res.body << endl;
}

void get_class_test_by_class_id(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(TEACHER_LOG, "get_class_test_by_class_id req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    
    Work work;
    vector<map<string,string>> info;
    info = work.get_test_by_id(value_r["class_id"].asString());
    if (info.empty()) {
        value_w["result"] = "false";
        value_w["error"] = "null";
        res.body = writer.write(value_w);
        return;
    }

    Json::Value value;
    for (size_t i = 0; i < info.size(); i++) {
        value.clear();
        for (auto it = info[i].begin(); it != info[i].end(); it++) {
            value[it->first] = it->second;
        }
        value_w.append(value);
    }
    res.body = writer.write(value_w);
    cout << res.body << endl;
}
