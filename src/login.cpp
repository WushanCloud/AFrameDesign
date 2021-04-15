#ifndef _LOGIN_CPP
#define _LOGIN_CPP

#include "login.h"

void login::runaction() {
    server->set_base_dir(www.c_str());
    action();
    server->listen("0.0.0.0", 19999);
}
void login::action() {
    server->Get(R"(.*)", GetFunction);
    server->Put(R"(.*)", PutFunction);
    server->Post(R"(.*)", PostFunction);
    server->Delete(R"(.*)", DeleteFunction);
}

void GetFunction(const httplib::Request& req, httplib::Response& res) {
    cout << req.method << endl;
    string function_name = req.path.substr(1);
    cout << function_name << endl;
    string err_str = req.method + " " + function_name + "\n" + req.body;
    for (auto it = req.params.begin(); it != req.params.end(); it++) {
        err_str += "\n" + it->first + "=" + it->second;
    }
    Log logerr;
    logerr.GeneralLog(LOG_PATH, err_str);

    function_ptr function = GetControll::getInstance()->get_mod(function_name);
    if (function == nullptr) {
        logerr.GeneralLog(ERR_LOG_PATH, err_str);
        function = GetControll::getInstance()->get_mod("other");
        return ;
    }
    function(req, res);
}
void PostFunction(const httplib::Request& req, httplib::Response& res) {
    cout << req.method << endl;
    string function_name = req.path.substr(1);
    cout << function_name << endl;
    string err_str = req.method + " " + function_name + "\n" + req.body;
    for (auto it = req.params.begin(); it != req.params.end(); it++) {
        err_str += "\n" + it->first + "=" + it->second;
    }
    Log logerr;
    logerr.GeneralLog(LOG_PATH, err_str);

    function_ptr function = PostControll::getInstance()->get_mod(function_name);
    if (function == nullptr) {
        logerr.GeneralLog(ERR_LOG_PATH, err_str);
        return ;
    }
    function(req, res); 
}
void PutFunction(const httplib::Request& req, httplib::Response& res) {
    cout << req.method << endl;
    string function_name = req.path.substr(1);
    cout << function_name << endl;
    string err_str = req.method + " " + function_name + "\n" + req.body;
    for (auto it = req.params.begin(); it != req.params.end(); it++) {
        err_str += "\n" + it->first + "=" + it->second;
    }
    Log logerr;
    logerr.GeneralLog(LOG_PATH, err_str);

    function_ptr function = PutControll::getInstance()->get_mod(function_name);
    if (function == nullptr) {
        logerr.GeneralLog(ERR_LOG_PATH, err_str);
        return ;
    }
    function(req, res); 
}
void DeleteFunction(const httplib::Request& req, httplib::Response& res) {
    cout << req.method << endl;
    string function_name = req.path.substr(1);
    cout << function_name << endl;
    string err_str = req.method + " " + function_name + "\n" + req.body;
    for (auto it = req.params.begin(); it != req.params.end(); it++) {
        err_str += "\n" + it->first + "=" + it->second;
    }
    Log logerr;
    logerr.GeneralLog(LOG_PATH, err_str);

    function_ptr function = DeleteControll::getInstance()->get_mod(function_name);
    if (function == nullptr) {
        logerr.GeneralLog(ERR_LOG_PATH, err_str);
        return ;
    }
    function(req, res); 
}

bool LoginToken(const httplib::Request& req, httplib::Response& res) {
    Log logerr;
    string err_str;
    // 检测账号密码是否正确
    Json::Reader reader;
    Json::Value value;
    bool ret = reader.parse(req.body, value);
    if (ret == false) {
        perror("LoginToken：Json：");
        logerr.GeneralLog(ERR_LOG_PATH, err_str + "LoginToken Json 解析失败 : " + req.body.c_str());
        return false;
    }


    string user_id = 
    // 为正确的账号密码生成Token，并返回给浏览器
    
}

bool CheckToken(const httplib::Request& req, httplib::Response& res);


#endif // _LOGIN_CPP
