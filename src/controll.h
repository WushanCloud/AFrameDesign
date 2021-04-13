#ifndef _CONTROLL_H
#define _CONTROLL_H

#include <string>
#include <unordered_map>
#include "../struct/httplib.h"
#include "../struct/log.h"

#include "./controller/student.h"

using namespace std;

typedef void* (*function_ptr) (const httplib::Request& req, httplib::Response& res);

class ControllBase
{
public:
    ~ControllBase();
    ControllBase(const ControllBase&) = delete;
    ControllBase& operator=(const ControllBase&) = delete;

    void push_mod(const string& function_name, function_ptr func_ptr);
    function_ptr get_mod(string function_name);

protected:
    ControllBase();
private:
    unordered_map<string, function_ptr> m;
};


#define PUSH_MOD(func) push_mod(#func, (function_ptr)func);

class GetControll : public ControllBase
{
    GetControll();
public:
    static GetControll* getInstance();
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

#endif // !_CONTROLL_H
