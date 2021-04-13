#include <iostream>
#include "httplib.h"
using namespace std;



int main ()
{
    httplib::Server ser;
    ser.Get("/a", [](const httplib::Request &req, httplib::Response &res){
            (void)req;
            res.set_header("Content-type", "application/json");
            res.set_header("Sek-Cookie","JSESSON=123123");
            });
    ser.listen("0.0.0.0", 16666);
    return 0;
}
