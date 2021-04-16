#ifndef _CONTROLL_CPP
#define _CONTROLL_CPP

#include "controll.h"

ControllBase::~ControllBase() {
    // std::cout << "destructor called!" << std::endl;
}

ControllBase::ControllBase() {
    //std::cout << "constructor called!" << std::endl;
}

void ControllBase::push_mod(const string& function_name, function_ptr func_ptr) {
    m.insert(pair<string, function_ptr>(function_name, (function_ptr)func_ptr));
}

function_ptr ControllBase::get_mod(string function_name) {
    auto fun = m.find(function_name);
    if (fun == m.end()) {
        return nullptr;
    }
    return fun->second;
}

GetControll* GetControll::getInstance() {
    static GetControll* instance = new GetControll;
    return instance;
}

PostControll* PostControll::getInstance() {
    static PostControll* instance = new PostControll;
    return instance;
}

PutControll* PutControll::getInstance() {
    static PutControll* instance = new PutControll;
    return instance;
}

DeleteControll* DeleteControll::getInstance() {
    static DeleteControll* instance = new DeleteControll;
    return instance;
}

GetControll::GetControll(){
    PUSH_MOD(get_student_name);
    PUSH_MOD(other);              
}

PostControll::PostControll(){
}

PutControll::PutControll(){
}

DeleteControll::DeleteControll(){
}
#endif // !_CONTROLL_CPP
