#include "class.h"

void add_class_base(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取要插入的班级信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "add_class_base req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string class_major = value_r["class_major"].asString();
    string class_class = value_r["class_class"].asString();

    ClassBase class_base;
    ret = class_base.add_class_base(class_major, class_class);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void delete_class_base(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "delete_class_base req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string number = value_r["class_base_id"].asString();

    ClassBase class_base;
    class_base.delete_class_base(number);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void get_class_base_by_major_class(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "get_class_base_by_major_class req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string class_major = value_r["class_major"].asString();
    string class_class = value_r["class_class"].asString();

    ClassBase class_base;
    map<string, string> info = class_base.get_info_by_major_class(class_major, class_class);
    if (info.empty()) {
        value_w["result"] = "false";
    }
    for (auto it = info.begin(); it != info.end(); it++) {
        value_w[it->first] = it->second;
    }
    value_w["result"] = "true";
    res.body = writer.write(value_w);
}

void get_class_base_by_id(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "get_class_base_by_id req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string class_base_id = value_r["class_base_id"].asString();

    ClassBase class_base;
    map<string, string> info = class_base.get_info_by_id(class_base_id);
    if (info.empty()) {
        value_w["result"] = "false";
    }
    for (auto it = info.begin(); it != info.end(); it++) {
        value_w[it->first] = it->second;
    }
    value_w["result"] = "true";
    res.body = writer.write(value_w);
}

void bind_class_base_and_student(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "bind_class_base_and_student req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string class_base_id = value_r["class_base_id"].asString();
    string student_number = value_r["student_number"].asString();

    ClassBase class_base;
    ret = class_base.add_class_student_base(class_base_id, student_number);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void get_class_allinfo_by_class_id(const httplib::Request& req, httplib::Response& res) {
    // 先查出所有班级学生学号
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "get_class_allinfo_by_class_id req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string class_base_id = value_r["class_base_id"].asString();

    ClassBase *class_base = new ClassBase;
    Student *student = new Student;
    vector<string> student_number_all;
    map<string, string> class_base_info;

    Json::Value tmp_v;
    map<string, string> tmp_m;
    class_base_info = class_base->get_info_by_id(class_base_id);
    student_number_all = class_base->get_all_student_number_by_id(class_base_id);
    for (size_t i = 0; i < student_number_all.size(); i++) {
        tmp_v.clear();
        for (auto it = class_base_info.begin(); it != class_base_info.end(); it++) {
            tmp_v[it->first] = it->second;
        }
        tmp_v["student_number"] = student_number_all[i];
        tmp_m = student->get_info_by_number(student_number_all[i]);
        tmp_v["student_name"] = tmp_m["student_name"];
        value_w.append(tmp_v);
    }

    res.body = writer.write(value_w);
    delete class_base;
    delete student;
}

/**
 * 课程相关
 */

void add_class(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "add_class req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    string class_name    = value_r["class_name"].asString();
    string class_base_id = value_r["class_base_id"].asString();
    string class_info    = value_r["class_info"].asString();

    // 根据班级编号查询到班级信息
    ClassBase class_base;
    map<string, string> class_base_info = class_base.get_info_by_id(class_base_id);
    if (class_base_info.empty()) {
        value_w["result"] = "false";
        value_w["error"] = "班级不存在";
        res.body = writer.write(value_w);
        return;
    }

    // 添加所有信息到课程创建表中
    Class class_;
    ret = class_.add_class(class_name, class_base_id, class_base_info["class_major"], class_base_info["class_class"], class_info);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void get_class_by_name_and_major(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "get_class_by_name_and_major req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }
    
    Class class_;
    vector<map<string,string>> class_info;
    class_info = class_.get_class_by_name_major(value_r["class_name"].asString(), value_r["class_major"].asString());
    if (class_info.empty()) {
        value_w["result"] = "false";
        value_w["error"] = "null";
        res.body = writer.write(value_w);
        return;
    }

    Json::Value value;
    for (size_t i = 0; i < class_info.size(); i++) {
        value.clear();
        for (auto it = class_info[i].begin(); it != class_info[i].end(); it++) {
            value[it->first] = it->second;
        }
        value_w.append(value);
    }
    res.body = writer.write(value_w);
}

void get_class_by_class_id(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "get_class_by_name_and_major req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    Class class_;
    map<string, string> info = class_.get_info_by_id(value_r["class_id"].asString());
    for (auto it = info.begin(); it != info.end(); it++) {
        value_w[it->first] = it->second;
    }
    value_w["result"] = "true";

    res.body = writer.write(value_w);
}

void delete_class_by_id(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "delete_class_by_id req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string number = value_r["class_id"].asString();

    Class class_;
    class_.delete_class(number);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void update_class_by_id(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "update_class_by_id req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string class_id = value_r["class_id"].asString();
    string class_base_id = value_r["class_base_id"].asString();
    string class_name = value_r["class_name"].asString();
    string class_info = value_r["class_info"].asString();

    // 根据班级编号查询到班级信息
    ClassBase class_base;
    map<string, string> class_base_info = class_base.get_info_by_id(class_base_id);
    if (class_base_info.empty()) {
        value_w["result"] = "false";
        value_w["error"] = "班级不存在";
        res.body = writer.write(value_w);
        return;
    }
    string class_major = class_base_info["class_major"];
    string class_class = class_base_info["class_class"];

    Class class_;
    ret = class_.update_class(class_id, class_name, class_base_id, class_major, class_class, class_info);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void bind_class_and_student(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取要插入的班级信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "bind_class_and_student req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string class_id = value_r["class_id"].asString();
    string student_number = value_r["student_number"].asString();

    Class class_;
    ret = class_.add_student_class(class_id, student_number);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}

void delete_class_and_student(const httplib::Request& req, httplib::Response& res) {
    Json::Value value_r;
    Json::Value value_w;
    Json::Reader reader;
    Json::FastWriter writer;

    // 获取要插入的班级信息
    bool ret = reader.parse(req.body, value_r);
    if (ret == false) {
        LOG(CLASS_LOG, "bind_class_and_student req的json解析失败");
        value_w["result"] = "false";
        res.body = writer.write(value_w);
        return;
    }

    string class_id = value_r["class_id"].asString();
    string student_number = value_r["student_number"].asString();

    Class class_;
    ret = class_.delete_student_class(class_id, student_number);
    if (ret == false) {
        value_w["result"] = "false";
    }
    else {
        value_w["result"] = "true";
    }
    res.body = writer.write(value_w);
}
