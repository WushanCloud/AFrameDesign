#include <iostream>
#include "httplib.h"

using namespace std;
using namespace httplib;

void hello(const Request &req, Response &res) {
    cout << req.body.c_str() << endl;
    res.set_content(req.body,"text/plain");
}

int main ()
{
    Server server;
    server.set_base_dir("./www");
    server.Get("/user", hello);

    server.listen("0.0.0.0", 9000);
    while (1);
    return 0;
}
