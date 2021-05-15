#ifndef _CLASS_H_
#define _CLASS_H_

#include "../../struct/httplib.h"
#include <jsoncpp/json/json.h>
#include <map>
#include "../../struct/log.h"
#include "../../struct/myredis.h"
#include "../service/user.h"

#define CLASS_LOG "../log/err_controller.log"

/**
 * �༶���
 */

// ���һ���༶
void add_class_base(const httplib::Request& req, httplib::Response& res);

// ɾ��һλ�༶
void delete_class_base(const httplib::Request& req, httplib::Response& res);

// ͨ���༶רҵ�Ͱ༶��Ų�༶��Ϣ
void get_class_base_by_major_class(const httplib::Request& req, httplib::Response& res);

// �󶨰༶��ѧ��
void bind_class_base_and_student(const httplib::Request& req, httplib::Response& res);

// ͨ���༶��Ų�ѯ�༶������ѧ����Ϣ
void get_class_allinfo_by_class_id(const httplib::Request& req, httplib::Response& res);


/**
 * �γ����
 */



#endif // !_CLASS_H_

