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
    bool GeneralLog(string path_name, string str, string author = "");
};

#endif // !_LOG_H