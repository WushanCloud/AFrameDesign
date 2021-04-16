#include <iostream>


#include <jsoncpp/json/json.h>




/*
#include "../struct/token.h"
#include "../struct/token.cpp"

int main() {
    Token token("1","41709050301");
    std::string s = token.GetToken();
    std::cout <<s << std::endl;
    return 0;
}
*/

#if 0

#include "../struct/db_connection.h"
int main() {
    DBconnect mysql_;
    mysql_.MysqlQuery("select student_id from student where student_number = 41709050301");
    MYSQL_RES* res = mysql_.MysqlResult();
    if (res == nullptr) {
        cout << "kong" << endl;
    }
    int len = mysql_.MysqlNumRow(res);
    cout << len << endl;

unsigned int num_fields;
unsigned int i;
MYSQL_FIELD *fields;
 
num_fields = mysql_num_fields(res);
fields = mysql_fetch_fields(res);
for(i = 0; i < num_fields; i++)
{
       printf("Field %u is %s\n", i, fields[i].name);

}

    return 0;
}

#endif 

//#include "myredis.h"
#if 0
using namespace std;
int main() {
    Redis red;
    redisReply* reply = red.Command("set foo hello");
    red.FreeReply(reply);
    reply = red.Command("get foo");
    cout << reply->str << endl;
    return 0;
}
#endif 
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
