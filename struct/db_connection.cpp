#ifndef _DB_CONNECTION_CPP
#define _DB_CONNECTION_CPP

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <mysql/mysql.h>
#include <jsoncpp/json/json.h>

#include "log.hpp"

#define MYSQL_HOST  "127.0.0.1"
#define MYSQL_USER  "root"
#define MYSQL_PASS  "111111"


class DBconnect
{
public:
	DBconnect(const std::string &db_name);
    bool MysqlQuery(const std::string& sql);
    MYSQL_RES* MysqlResult();
    int MysqlNumFields(MYSQL_RES* res);
    int MysqlNumRow(MYSQL_RES* res);
    MYSQL_ROW MysqlFetchRow(MYSQL_RES* res);
    bool MysqlFreeResult(MYSQL_RES* res);
    ~DBconnect()
    {
        if (mysql)
        {
            mysql_close(mysql);
        }
    }
private:
	string db_name;
    MYSQL* mysql;
    
    logspace::Log log;
    const string log_dir = "../log/mysql_connection.log";
};

DBconnect::DBconnect(const std::string &dbname)
{
    this->db_name = dbname;
    // 初始化mysql句柄
    this->mysql = mysql_init(NULL);
    if (mysql == NULL) {
        std::string error = "mysql init error :";
        log.GeneralLog(log_dir, error + mysql_error(mysql));
    }
    // 选择mysql服务器
    if (!mysql_real_connect(this->mysql, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, this->db_name, 0, NULL, 0)) {
        printf("mysql connect error : %s\n", mysql_error(mysql));
        mysql_close(this->mysql);
    }
    // 设置连接的数据库
    if (mysql_select_db(this->mysql, this->db_name)) {
        printf("mysql database select error : %s\n", mysql_error(mysql));
        mysql_close(this->mysql);
    }
    // 设置字符编码集
    if (mysql_set_character_set(this->mysql, "utf8")) {
        printf("set character error : %s\n", mysql_error(mysql));
        mysql_close(this->mysql);
    }
}

bool DBconnect::MysqlQuery(const std::string& sql)
{
    if (mysql_query(this->mysql, sql.c_str())){
        printf("sql : %s  false : %s\n", sql.c_str(), mysql_error(mysql));
        return false;
    }
    return true;
}

MYSQL_RES* DBconnect::MysqlResult()
{
    // 获取结果集
    MYSQL_RES* res = mysql_store_result(this->mysql);
    if (res == NULL) {
        printf("Get results fail : %s\n", mysql_error(_mysql));
        return nullptr;
    }
    return res;
}

int DBconnect::MysqlNumFields(MYSQL_RES* res)
{
    return mysql_num_fields(res);
}

int DBconnect::MysqlNumRow(MYSQL_RES* res)
{
    return mysql_num_rows(res);
}

MYSQL_ROW DBconnect::MysqlFetchRow(MYSQL_RES* res)
{
    return mysql_fetch_row(res);
}

bool DBconnect::MysqlFreeResult(MYSQL_RES* res)
{
    mysql_free_result(res);
    return true;
}
#endif // !DB_CONNECTION_CPP