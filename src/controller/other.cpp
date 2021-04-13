#ifndef _OTHER_CPP
#define _OTHER_CPP 

#include "other.h"

void other(const httplib::Request& req, httplib::Response& res) {
    if (req.path.substr(1) == "favicon.ico") {
        res.set_content("1", "text/plain");
        return;                            
    }
    res.set_content("hello", "text/plain");
}

void get_pages(const httplib::Request& req, httplib::Response& res) {
    std::cout << 1 << std::endl;
    int user_type = stoi(req.get_param_value("usertype"));
    if (user_type == 2) {
        res.set_redirect("index2.html");
    }
}
#endif // !_OTHER_CPP
