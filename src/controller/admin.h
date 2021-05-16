#ifndef _ADMIN_H
#define _ADMIN_H

#include "../../struct/httplib.h"
#include <jsoncpp/json/json.h>
#include "../../struct/log.h"
#include "../../struct/myredis.h"
#include "../service/user.h"

#define ADMIN_LOG "../log/err_controller.log"

void get_admin_name(const httplib::Request& req, httplib::Response& res); 

void update_admin_passwd(const httplib::Request& req, httplib::Response& res);

#endif // _ADMIN_H
