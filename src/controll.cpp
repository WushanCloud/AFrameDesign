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
    return fun->second;
}

GetControll* GetControll::getInstance() {
    static GetControll* instance = new GetControll;
    return instance;
}


GetControll::GetControll(){
          cout << "GetControll" << endl;
                PUSH_MOD(get_student_name);
                  
}

#endif // !_CONTROLL_CPP
