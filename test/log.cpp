#ifndef _LOG_HPP
#define _LOG_HPP

#include "log.h"

bool Log::GeneralLog(const string& path_name, const string& str, string author) {
    ofstream ofs;
    time_t now;
    cout << "log+1" << endl;
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
