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
    PUSH_MOD(get_admin_name);
    PUSH_MOD(get_teacher_name);
    PUSH_MOD(other);              
}

PostControll::PostControll(){
    PUSH_MOD(update_admin_passwd);

    PUSH_MOD(get_teacher_info_by_name);
    PUSH_MOD(get_teacher_info_by_number);
    PUSH_MOD(add_teacher);
    PUSH_MOD(update_teacher_passwd);
    PUSH_MOD(delete_teacher);

    PUSH_MOD(add_student);
    PUSH_MOD(get_student_info_by_name);
    PUSH_MOD(get_student_info_by_number);
    PUSH_MOD(delete_student);
    PUSH_MOD(update_student_passwd);

    PUSH_MOD(add_class_base);
    PUSH_MOD(delete_class_base);
    PUSH_MOD(get_class_base_by_major_class);
    PUSH_MOD(get_class_base_by_id);
    PUSH_MOD(bind_class_base_and_student);
    PUSH_MOD(get_class_allinfo_by_class_id);

    PUSH_MOD(add_class);
    PUSH_MOD(get_class_by_name_and_major);
    PUSH_MOD(get_class_by_class_id);
    PUSH_MOD(delete_class_by_id);
    PUSH_MOD(update_class_by_id);
    PUSH_MOD(bind_class_and_student);
    PUSH_MOD(delete_class_and_student);
}

PutControll::PutControll(){
}

DeleteControll::DeleteControll(){
}
#endif // !_CONTROLL_CPP
