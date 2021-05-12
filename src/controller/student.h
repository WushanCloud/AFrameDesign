#ifndef _STUDENT_H
#define _STUDENT_H

#include "../../struct/httplib.h"
#include <jsoncpp/json/json.h>

void get_student_name(const httplib::Request& req, httplib::Response& res); 


#endif // _STUDENT_H
