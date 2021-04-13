#ifndef _DB_CONNECTION_H
#define _DB_CONNECTION_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <mysql/mysql.h>
#include <jsoncpp/json/json.h>

#include "log.h"

#define MYSQL_HOST  "127.0.0.1"
#define MYSQL_USER  "root"
#define MYSQL_PASS  "111111"


class DBconnect
{
public:
    // 数据库的初始化，链接
    DBconnect(const std::string& db_name);
    // 数据库语句执行
    bool MysqlQuery(const std::string& sql);
    // 获取执行结果集
    MYSQL_RES* MysqlResult();
    // 获取列数
    int MysqlNumFields(MYSQL_RES* res);
    // 获取行数
    int MysqlNumRow(MYSQL_RES* res);
    // 获取一行结果
    MYSQL_ROW MysqlFetchRow(MYSQL_RES* res);
    // 释放结果集
    bool MysqlFreeResult(MYSQL_RES* res);
    
    ~DBconnect();

private:

    string db_name;

    MYSQL* mysql;

    Log log;

    const string log_dir = "../log/mysql_connection.log";
};

#endif // _DB_CONNECTION_H
