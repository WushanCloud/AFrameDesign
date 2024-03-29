#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

/**
 * 日志类
 * 功能：把文本写入指定文件
 **/
class Log {
public:
    bool GeneralLog(const string& path_name, const string& str, string author = "");
};

class SubLog {
public:
    static bool GeneralLog(const string& path_name, const string& file, int line, const string& str);
};

#define LOG(x, y) SubLog::GeneralLog(x, __FILE__, __LINE__, y)
#endif // !_LOG_H
