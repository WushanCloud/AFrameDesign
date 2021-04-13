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
    string function_name = req.path.substr(1);
    cout << function_name << endl;
    Log logerr;
    logerr.GeneralLog(ERR_LOG_PATH, "get"+function_name);
    function_ptr function = GetControll::getInstance()->get_mod(function_name);
    cout << "1" << endl;
    function(req, res);
    cout << "2" << endl;
}
void PostFunction(const httplib::Request& req, httplib::Response& res) {

}
void PutFunction(const httplib::Request& req, httplib::Response& res) {

}
void DeleteFunction(const httplib::Request& req, httplib::Response& res) {

}

#endif // _LOGIN_CPP
