#ifndef _LOG_HPP
#define _LOG_HPP

#include "log.h"

bool Log::GeneralLog(const string& path_name, const string& str, string author) {
    ofstream ofs;
    time_t now;
    ofs.open(path_name, ios::out | ios::app);
    if (!ofs.is_open()) {
        perror("open Log file false!");
        return false;
    }
    struct tm * timeinfo;
    time(&now);
    timeinfo = localtime(&now);
    string s = asctime(timeinfo);
    s.pop_back();
    if (author != "") {
        ofs << s << " [" << __FILE__ << "]: " << __LINE__  << " " << author << " "<< str  << endl;
    } else {
        ofs << s << " [" << __FILE__ << "]: " << __LINE__  << " " << str  << endl;
    }
    ofs.close();
    return true;
}

bool SubLog::GeneralLog(const string& path_name, const string& file, int line, const string& str) {
    ofstream ofs;
    time_t now;
    ofs.open(path_name, ios::out | ios::app);
    if (!ofs.is_open()) {
        perror("open Log file false!");
        return false;
    }
    struct tm * timeinfo;
    time(&now);
    timeinfo = localtime(&now);
    string s = asctime(timeinfo);
    s.pop_back();
    ofs << s << " [" << file << "]: " << line << " " << str << endl;
    ofs.close();
    return true;
}
#endif // _LOG_HPP
