#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

/**
 * ��־��
 * ���ܣ����ı�д��ָ���ļ�
 **/
class Log {
public:
    bool GeneralLog(const string& path_name, const string& str, string author = "");
};

#endif // !_LOG_H
