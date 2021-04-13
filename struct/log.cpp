#ifndef _LOG_HPP
#define _LOG_HPP

#include "log.h"

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
#endif // _LOG_HPP
