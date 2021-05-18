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

// ͨ���༶��Ų�༶��Ϣ
void get_class_base_by_id(const httplib::Request& req, httplib::Response& res);

// �󶨰༶��ѧ��
void bind_class_base_and_student(const httplib::Request& req, httplib::Response& res);

// ͨ���༶��Ų�ѯ�༶������ѧ����Ϣ
void get_class_allinfo_by_class_id(const httplib::Request& req, httplib::Response& res);


/**
 * �γ����
 */

// ����һ���γ�
void add_class(const httplib::Request& req, httplib::Response& res);

// ͨ���γ����Ϳγ�רҵ��ѯ�γ�
void get_class_by_name_and_major(const httplib::Request& req, httplib::Response& res);

// ͨ���γ̱�Ų�ѯ�γ�
void get_class_by_class_id(const httplib::Request& req, httplib::Response& res);

// ͨ���γ̱�Ų�ѯ�ڿν�ʦ
void get_teacher_by_class_id(const httplib::Request& req, httplib::Response& res);

// ͨ���γ̱��ɾ���γ�
void delete_class_by_id(const httplib::Request& req, httplib::Response& res);

// ͨ���γ̱���޸Ŀγ�
void update_class_by_id(const httplib::Request& req, httplib::Response& res);

// ��ѧ���Ϳγ�
void bind_class_and_student(const httplib::Request& req, httplib::Response& res);

// ͨ���γ̱�Ų�ѯ����ѧ��
void get_all_student_by_class_id(const httplib::Request& req, httplib::Response& res);

// �󶨽�ʦ�Ϳγ�
void bind_class_and_teacher(const httplib::Request& req, httplib::Response& res);

// �ӿγ�ɾ��ѧ��
void delete_class_and_student(const httplib::Request& req, httplib::Response& res);

// �ӿγ�ɾ����ʦ
void delete_class_and_teacher(const httplib::Request& req, httplib::Response& res);
#endif // !_CLASS_H_

