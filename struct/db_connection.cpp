#ifndef _DB_CONNECTION_CPP
#define _DB_CONNECTION_CPP

#include "db_connection.h"

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
    if (!mysql_real_connect(this->mysql, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, this->db_name.c_str(), 0, NULL, 0)) {
        printf("mysql connect error : %s\n", mysql_error(mysql));
        mysql_close(this->mysql);
    }
    // 设置连接的数据库
    if (mysql_select_db(this->mysql, this->db_name.c_str())) {
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
        printf("Get results fail : %s\n", mysql_error(mysql));
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

MYSQL_FIELD* DBconnect::MysqlFetchFields(MYSQL_RES* res)
{
    return mysql_fetch_fields(res);
}

bool DBconnect::MysqlFreeResult(MYSQL_RES* res)
{
    mysql_free_result(res);
    return true;
}

DBconnect::~DBconnect()
{
    if (mysql)
    {
        mysql_close(mysql);
    }
}
#endif // !DB_CONNECTION_CPP
