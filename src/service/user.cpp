#include "user.h"

std::string Student::get_passwd_by_number(const std::string& student_number)
{
	std::lock_guard<std::mutex> lock(mysql_db._mutex);
	trim(student_number);
	std::string sql = "select student_passwd from student where student_number = " + student_number;
	mysql_db.MysqlQuery(sql);
	MYSQL_RES * res = mysql_db.MysqlResult();
	if (res == false) {
		return "0";
	}
	int len = mysql_db.MysqlNumRow(res);
	if (len == 0) {
		mysql_db.MysqlFreeResult(res);
		return "1";
	}
	MYSQL_RES row;
	row = mysql_db.MysqlFetchRow(res);
	mysql_db.MysqlFreeResult(res);
	return row[0];
}

std::map<std::string, std::string> Student::get_info_by_number(const std::string& student_number)
{
	std::lock_guard<std::mutex> lock(mysql_db._mutex);
	trim(student_number);
	std::map<std::string, std::string> m_ss;
	std::string sql = "select * from student where student_number = " + student_number;
	mysql_db.MysqlQuery(sql);
	MYSQL_RES* res = mysql_db.MysqlResult();
	int len = mysql_db.MysqlNumRow(res);
	if (len == 0) {
		mysql_db.MysqlFreeResult(res);
		return m_ss;
	}
	MYSQL_RES row;
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
	trim(student_number);
	std::vector<std::string> v_s
	std::string sql = "SELECT class_id FROM student_class where student_id = " + student_id;
	mysql_db.MysqlQuery(sql);
	MYSQL_RES* res = mysql_db.MysqlResult();
	if (res == false) {
		return nullptr;
	}
	int len = mysql_db.MysqlNumRow(res);
	if (len == 0) {
		mysql_db.MysqlFreeResult(res);
		return v_s;
	}
	MYSQL_RES row;
	for (int i = 0; i < len; i++) {
		row = mysql_db.MysqlFetchRow(res);
		v_s.push_back(row[0]);
	}
	mysql_db.MysqlFreeResult(res);
	return v_s;
}

//C++ 去字符串两边的空格
void trim(std::string& s) {
    if (s.empty()) {
        return;
    }
	string blanks("\f\v\r\t\n ");
	s.erase(0, s.find_first_not_of(blanks));
	s.erase(s.find_last_not_of(blanks) + 1);
}