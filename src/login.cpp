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
    string err_str = req.method + " " + function_name + " " + req.body;
    Log logerr;
    logerr.GeneralLog(LOG_PATH, err_str);
    
    //    if (CheckToken(req, res) == false) {
    //        return ;
    //    }
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
    cout << req.body << endl;
    cout << function_name << endl;
    string err_str = req.method + " " + function_name + " " + req.body;
    Log logerr;
    logerr.GeneralLog(LOG_PATH, err_str);

    // 登录逻辑
    if (function_name == "login") {
        LoginToken(req, res);
        return ;
    } else {
    //    if (CheckToken(req, res) == false) {
    //        return ;
    //    }
    }

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
    string err_str = req.method + " " + function_name + " " + req.body;
    Log logerr;
    logerr.GeneralLog(LOG_PATH, err_str);

   //     if (CheckToken(req, res) == false) {
   //         return ;
   //     }
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
    string err_str = req.method + " " + function_name + " " + req.body;
    Log logerr;
    logerr.GeneralLog(LOG_PATH, err_str);

   //     if (CheckToken(req, res) == false) {
   //         return ;
   //     }
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
    // 解析账号密码
    Json::Reader reader;
    Json::Value value;
    cout << "LoginToken 函数内："<< req.body<< endl;
    bool ret = reader.parse(req.body, value);
    if (ret == false) {
        logerr.GeneralLog(ERR_LOG_PATH, err_str + "LoginToken Json 解析失败 : " + req.body.c_str());
        return false;
    }
    // 验证账号密码是否正确
    std::string user_type = value["user_type"].asString();
    std::string user_number = value["user_number"].asString();
    std::string user_passwd = value["user_passwd"].asString();
    int check_num = check_user(user_type, user_number, user_passwd);

    Json::Value value2; // 用于返回的json
    Json::FastWriter writer;
    if (check_num == 0) {
        // 为正确的账号密码生成Token，并返回给浏览器
        Token token(user_type, user_number);
        std::cout << token.GetToken() << std::endl;
        res.set_header("Set-Cookie", token.GetToken().c_str());
        res.set_header("Content-Type", "application/json");
        // 返回登录的验证结果
        value2["result"] = "0";
        res.body = writer.write(value2);
        //登录信息注册到redis
        Redis redis;
        std::string command = "hset " + token.GetToken() + " user_type " + user_type;
        redisReply* reply = redis.Command(command);
        if (reply->integer != 1) {
            return false;
        }
        redis.Command("hset " + token.GetToken() + " user_number " + user_number);
        redis.Command("expire " + token.GetToken() + " 13600");
        return true;
    } else {
        value2["result"] = "1";
        res.body = writer.write(value2);
        return false;
    }
}

bool CheckToken(const httplib::Request& req, httplib::Response& res) {
    string err_str;
    // 获取浏览器页面的token信息
    std::string token = req.get_header_value("Cookie");
    // 检测token是否在redis中
    Redis redis;
    std::string command = "EXISTS " + token;
    redisReply* ret = redis.Command(command);
    if (ret->integer == 0) {
        //res.set_redirect("index.html");
        return false;
    }
    return true;
}


#endif // _LOGIN_CPP
