#ifndef _CONTROLL_CPP
#define _CONTROLL_CPP

#include <string>
#include <unordered_map>

using namespace std;

typedef void* (*function_ptr) (const httplib::Request& req, httplib::Response& res);

class ControllBase
{
public:
    ~ControllBase() {
        // std::cout << "destructor called!" << std::endl;
    }
    ControllBase(const ControllBase&) = delete;
    ControllBase& operator=(const ControllBase&) = delete;
    static ControllBase* getInstance() {
        static ControllBase instance;
        return &instance;
    }
    void push_mod(const string& function_name, function_ptr func_ptr) {
        m.insert(pair<string, function_ptr>(function_name, (function_ptr)func_ptr));
    }
    function_ptr get_mod(string function_name) {
        auto fun = m.find(function_name);
        return fun->second;
    }

private:
    unordered_map<string, function_ptr> m;
    ControllBase() {
        //std::cout << "constructor called!" << std::endl;
    }
};

class GetControll : public ControllBase
{
};
class PostControll : public ControllBase
{
};
class PutControll : public ControllBase
{
};
class DeleteControll : public ControllBase
{
};

#endif // !_CONTROLL_CPP
