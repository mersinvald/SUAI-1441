#include "AbstractDocument.hpp"

std::ostream& operator<< (std::ostream& os, const AbstractDocument& obj) {
    obj.write(os);
    return os;
}

std::istream& operator>> (std::istream& is, AbstractDocument& obj) {
    obj.read(is);
    return is;
}

time_t
AbstractDatedDocument::getDate(std::istream& is) {
    tm date {};

    std::string s;
    is >> s;
    std::stringstream ss;
    ss << s;

    char delim = '.';
    for(int i = 0; i < 3; i++) {
        getline(ss, s, delim);
        if(s[0] == '\n') {
            s.erase(s.begin(), s.begin()+1);
        }
        switch(i) {
        case 0: date.tm_mday = std::stoi(s); break;
        case 1: date.tm_mon  = std::stoi(s); delim = '\n'; break;
        case 2: date.tm_year = std::stoi(s); break;
        }
    }
    return timelocal(&date);
}

void
AbstractDatedDocument::printTime(std::ostream& os, time_t time) {
    tm* date = localtime(&time);
    os << std::setw(2) << std::setfill('0') << date->tm_mday << "."
       << std::setw(2) << std::setfill('0') << date->tm_mon << "."
       << date->tm_year
       << " ";
}
