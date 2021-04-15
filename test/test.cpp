#include <iostream>
#include "myredis.h"

using namespace std;
int main() {
    Redis red;
    redisReply* reply = red.Command("set foo hello");
    red.FreeReply(reply);
    reply = red.Command("get foo");
    cout << reply->str << endl;
    return 0;
}

#if 0
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

#endif
