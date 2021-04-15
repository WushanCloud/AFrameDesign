#ifndef _DB_CONNECTION_H
#define _DB_CONNECTION_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <mysql/mysql.h>
#include <jsoncpp/json/json.h>
#include <mutex>

#include "log.h"

#define MYSQL_HOST  "127.0.0.1"
#define MYSQL_USER  "root"
#define MYSQL_PASS  "111111"


class DBconnect
{
public:
    // ���ݿ�ĳ�ʼ��������
    DBconnect(const std::string& db_name = "teachSystem");
    // ���ݿ����ִ��
    bool MysqlQuery(const std::string& sql);
    // ��ȡִ�н����
    MYSQL_RES* MysqlResult();
    // ��ȡ����
    int MysqlNumFields(MYSQL_RES* res);
    // ��ȡ����
    int MysqlNumRow(MYSQL_RES* res);
    // ��ȡһ�н��
    MYSQL_ROW MysqlFetchRow(MYSQL_RES* res);
    // ��ȡ����������ݱ��ͷ
    MYSQL_FIELD* MysqlFetchFields(MYSQL_RES* res);
    // �ͷŽ����
    bool MysqlFreeResult(MYSQL_RES* res);
    
    ~DBconnect();

private:

    string db_name;

    MYSQL* mysql;

    std::mutex _mutex;

    Log log;

    const string log_dir = "../log/mysql_connection.log";
};

#endif // _DB_CONNECTION_H
