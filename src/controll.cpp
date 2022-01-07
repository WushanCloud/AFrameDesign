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
    PUSH_MOD(test);
    PUSH_MOD(get_student_name);
    PUSH_MOD(get_admin_name);
    PUSH_MOD(get_teacher_name);
    PUSH_MOD(other);              

    // 教师
    PUSH_MOD(get_teacher_class);

    // 学生
    PUSH_MOD(get_classmate);
    PUSH_MOD(get_student_info);
    PUSH_MOD(get_student_class);
}

PostControll::PostControll(){
    PUSH_MOD(test);
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
    PUSH_MOD(bind_class_and_teacher);
    PUSH_MOD(delete_class_and_teacher);
    PUSH_MOD(get_teacher_by_class_id);
    PUSH_MOD(get_all_student_by_class_id);

    // 教师
    PUSH_MOD(add_class_work);
    PUSH_MOD(add_class_test);
    PUSH_MOD(get_class_work_by_class_id);
    PUSH_MOD(get_class_test_by_class_id);
    PUSH_MOD(get_class_work_by_class_work_id);
    PUSH_MOD(get_class_test_by_class_test_id);
    PUSH_MOD(add_class_work_title);
    PUSH_MOD(add_class_test_title);
    PUSH_MOD(get_work_topic_by_class_work_id);
    PUSH_MOD(get_test_topic_by_class_test_id);

    PUSH_MOD(add_student_work_answer);
    PUSH_MOD(add_student_test_answer);
}

PutControll::PutControll(){
    PUSH_MOD(test);
}

DeleteControll::DeleteControll(){
    PUSH_MOD(test);
}
#endif // !_CONTROLL_CPP
