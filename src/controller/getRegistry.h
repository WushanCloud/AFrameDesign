#include "student.h"

#define PUSH_MOD(func) push_mod("func", (function_ptr)func);

GetControll::GetControll(){
    PUSH_MOD(get_student_name);
}
