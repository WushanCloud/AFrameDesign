#include "../struct/httplib.h"
#include "controll.cpp"

class login{
    public:
        httplib::Server *server = new httplib::Server;

        void runaction();
        void action();
    private:
        const std::string www = "./www"; 
        ControllBase * contr_Bi = ControllBase::getInstance(); 
};

void login::runaction() {
    server->set_base_dir(www.c_str());
    action();
    server->listen("0.0.0.0", 19999);
}
void login::action() {
    //server->Get("R(.*)", );
}
