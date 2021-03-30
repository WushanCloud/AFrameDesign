#ifndef _LOG_HPP
#define _LOG_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;
namespace logspace{

/**
 * 日志类
 * 功能：把文本写入指定文件
 **/
class Log{
    public:
        bool GeneralLog(string path_name, string str, string author = "");
};

bool Log::GeneralLog(string path_name, string str, string author) {
    ofstream ofs;
    time_t now;

    ofs.open(path_name, ios::app);
    struct tm * timeinfo;
    time(&now);
    timeinfo = localtime(&now);
    string s = asctime(timeinfo);
    s.pop_back();
    if (author != "") {
        ofs << s << " " << author << " "<< str  << endl;
    } else {
        ofs << s << " " << str  << endl;
    }
    ofs.close();
    return true;
}
}
#endif // _LOG_HPP
