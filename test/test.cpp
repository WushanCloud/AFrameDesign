#include <iostream>
#include "httplib.h"

using namespace std;
using namespace httplib;

void hello(const Request &req, Response &res) {
    res.set_content("hello world!", "text/plain");
}

int main ()
{
    Server server;
    server.set_base_dir("./www");
    server.Get("/", hello);

    server.listen("0.0.0.0", 9000);
    while (1);
    return 0;
}
