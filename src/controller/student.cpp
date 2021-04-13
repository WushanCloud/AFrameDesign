#include "student.h"

void get_student_name(const httplib::Request& req, httplib::Response& res) {
    res.set_content("Hello World!", "text/plain");
}
    

