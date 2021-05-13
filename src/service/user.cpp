#include "user.h"

std::string Student::get_passwd_by_number(const std::string& student_number)
{
	std::lock_guard<std::mutex> lock(mysql_db._mutex);
    std::string student_num = student_number;
    trim(student_num);
	std::string sql = "select student_passwd from student where student_number = " + student_num;
	mysql_db.MysqlQuery(sql);
	MYSQL_RES * res = mysql_db.MysqlResult();
	if (res == nullptr) {
		return "0";
	}
	int len = mysql_db.MysqlNumRow(res);
	if (len == 0) {
		mysql_db.MysqlFreeResult(res);
		return "1";
	}
	MYSQL_ROW row;
	row = mysql_db.MysqlFetchRow(res);
	mysql_db.MysqlFreeResult(res);
	return row[0];
}

std::map<std::string, std::string> Student::get_info_by_number(const std::string& student_number)
{
	std::lock_guard<std::mutex> lock(mysql_db._mutex);
    std::string student_num =student_number;
    trim(student_num);
	std::map<std::string, std::string> m_ss;
	std::string sql = "select * from student where student_number = " + student_num;
	mysql_db.MysqlQuery(sql);
	MYSQL_RES* res = mysql_db.MysqlResult();
	int len = mysql_db.MysqlNumRow(res);
	if (len == 0) {
		mysql_db.MysqlFreeResult(res);
		return m_ss;
	}
	MYSQL_ROW row;
	row = mysql_db.MysqlFetchRow(res);
	mysql_db.MysqlFreeResult(res);

	MYSQL_FIELD* fields;
	unsigned int num_fields = mysql_db.MysqlNumFields(res);
	fields = mysql_fetch_fields(res);
	for (unsigned int i = 0; i < num_fields; i++) {
		m_ss[fields[i].name] = row[i];
	}
	return m_ss;
}

std::vector<std::string> Student::get_class_by_id(const std::string& student_id)
{
	std::lock_guard<std::mutex> lock(mysql_db._mutex);
    std::string student_id_ = student_id;
    trim(student_id_);
	std::vector<std::string> v_s;
	std::string sql = "SELECT class_id FROM student_class where student_id = " + student_id_;
	mysql_db.MysqlQuery(sql);
	MYSQL_RES* res = mysql_db.MysqlResult();
	int len = mysql_db.MysqlNumRow(res);
	if (len == 0) {
		mysql_db.MysqlFreeResult(res);
		return v_s;
	}
	MYSQL_ROW row;
	for (int i = 0; i < len; i++) {
		row = mysql_db.MysqlFetchRow(res);
		v_s.push_back(row[0]);
	}
	mysql_db.MysqlFreeResult(res);
	return v_s;
}

void trim(std::string& s) {
    if (s.empty()) {
        return;            
    }
    string blanks("\f\v\r\t\n ");
    s.erase(0, s.find_first_not_of(blanks));
    s.erase(s.find_last_not_of(blanks) + 1);
}

std::string Teacher::get_passwd_by_number(const std::string& teacher_number)
{
	std::lock_guard<std::mutex> lock(mysql._mutex);
	std::string sql = "select teacher_passwd from teacher where teacher_number = " + teacher_number;
	mysql.MysqlQuery(sql);
	MYSQL_RES* res = mysql.MysqlResult();
	if (res == nullptr) {
		return "0";
	}
	int len = mysql.MysqlNumRow(res);
	if (len == 0) {
		mysql.MysqlFreeResult(res);
		return "1";
	}
	MYSQL_ROW row;
	row = mysql.MysqlFetchRow(res);
	mysql.MysqlFreeResult(res);
	return row[0];
}

std::map<std::string, std::string> Teacher::get_info_by_number(const std::string& teacher_number)
{
	std::lock_guard<std::mutex> lock(mysql._mutex);
	std::map<std::string, std::string> m_ss;
	std::string sql = "select * from teacher where teacher_number = '" + teacher_number + "'";
	mysql.MysqlQuery(sql);
	MYSQL_RES* res = mysql.MysqlResult();
	int len = mysql.MysqlNumRow(res);
	if (len == 0) {
		mysql.MysqlFreeResult(res);
		return m_ss;
	}
	MYSQL_ROW row;
	row = mysql.MysqlFetchRow(res);
	mysql.MysqlFreeResult(res);

	MYSQL_FIELD* fields;
	unsigned int num_fields = mysql.MysqlNumFields(res);
	fields = mysql_fetch_fields(res);
	for (unsigned int i = 0; i < num_fields; i++) {
		m_ss[fields[i].name] = row[i];
	}
	return m_ss;
}

std::map<std::string, std::string> Teacher::get_info_by_name(const std::string& teacher_name) {
	std::lock_guard<std::mutex> lock(mysql._mutex);
	std::map<std::string, std::string> m_ss;
	std::string sql = "select * from teacher where teacher_name = '" + teacher_name + "'";
	mysql.MysqlQuery(sql);
	MYSQL_RES* res = mysql.MysqlResult();
	int len = mysql.MysqlNumRow(res);
	if (len == 0) {
		mysql.MysqlFreeResult(res);
		return m_ss;
	}
	MYSQL_ROW row;
	row = mysql.MysqlFetchRow(res);
	mysql.MysqlFreeResult(res);

	MYSQL_FIELD* fields;
	unsigned int num_fields = mysql.MysqlNumFields(res);
	fields = mysql_fetch_fields(res);
	for (unsigned int i = 0; i < num_fields; i++) {
		m_ss[fields[i].name] = row[i];
	}
	return m_ss;
}

std::vector<std::string> Teacher::get_class_by_id(const std::string& teacher_id)
{
	std::lock_guard<std::mutex> lock(mysql._mutex);
	std::vector<std::string> v_s;
	std::string sql = "SELECT class_id FROM teacher_class where teacher_id = " + teacher_id;
	mysql.MysqlQuery(sql);
	MYSQL_RES* res = mysql.MysqlResult();
	int len = mysql.MysqlNumRow(res);
	if (len == 0) {
		mysql.MysqlFreeResult(res);
		return v_s;
	}
	MYSQL_ROW row;
	for (int i = 0; i < len; i++) {
		row = mysql.MysqlFetchRow(res);
		v_s.push_back(row[0]);
	}
	mysql.MysqlFreeResult(res);
	return v_s;
}

bool Teacher::add_teacher(const std::string& teacher_number, const std::string& teacher_name, const std::string& teacher_passwd) {
	std::lock_guard<std::mutex> lock(mysql._mutex);
    std::string sql = "insert into teacher values('','" + teacher_number + "', '" + teacher_name + "', '" + teacher_passwd + "')";
	bool ret = mysql.MysqlQuery(sql);
    return ret;
}

bool Teacher::delete_teacher(const std::string& teacher_number, const std::string& teacher_name) {
	std::lock_guard<std::mutex> lock(mysql._mutex);
    (void)teacher_name;
    std::string sql = "delete from teacher where teacher_number = '" + teacher_number + "'";
	bool ret = mysql.MysqlQuery(sql);
    return ret;
}

bool Teacher::update_passwd(const std::string& teacher_number, const std::string& teacher_passwd) {
	std::lock_guard<std::mutex> lock(mysql._mutex);
    std::string sql = "update teacher set teacher_passwd = '" + teacher_passwd + "' where teacher_number = '" + teacher_number + "'";
	bool ret = mysql.MysqlQuery(sql);
    return ret;
}

std::string Admin::get_passwd_by_number(const std::string& admin_number)
{
	std::lock_guard<std::mutex> lock(mysql._mutex);
	std::string sql = "select admin_passwd from admin where admin_number = " + admin_number;
	mysql.MysqlQuery(sql);
	MYSQL_RES* res = mysql.MysqlResult();
	if (res == nullptr) {
		return "0";
	}
	int len = mysql.MysqlNumRow(res);
	if (len == 0) {
		mysql.MysqlFreeResult(res);
		return "1";
	}
	MYSQL_ROW row;
	row = mysql.MysqlFetchRow(res);
	mysql.MysqlFreeResult(res);
	return row[0];
}

std::string Admin::get_name_by_number(const std::string& admin_number)
{
	std::lock_guard<std::mutex> lock(mysql._mutex);
	std::string sql = "select admin_name from admin where admin_number = " + admin_number;
	mysql.MysqlQuery(sql);
	MYSQL_RES* res = mysql.MysqlResult();
	if (res == nullptr) {
		return "0";
	}
	int len = mysql.MysqlNumRow(res);
	if (len == 0) {
		mysql.MysqlFreeResult(res);
		return "1";
	}
	MYSQL_ROW row;
	row = mysql.MysqlFetchRow(res);
	mysql.MysqlFreeResult(res);
	return row[0];
}
