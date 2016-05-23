#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <iomanip>

class AbstractDocument {
public:
    friend class DocumentManager;

    explicit AbstractDocument(int type, bool dated)
        : type(type), dated(dated), name(""), secondName("") {}

    virtual ~AbstractDocument() {}

    virtual void          promt() = 0;
    virtual std::ostream& write (std::ostream& os) const = 0;
    virtual std::istream& read (std::istream& is) = 0;

    friend std::ostream& operator<< (std::ostream& os, const AbstractDocument& obj) {
        obj.write(os);
        return os;
    }

    friend std::istream& operator>> (std::istream& is, AbstractDocument& obj) {
        obj.read(is);
        return is;
    }

protected:
    const int   type;
    bool        dated;
    std::string name;
    std::string secondName;
};

class AbstractDatedDocument : public AbstractDocument {
public:
    friend class DocumentManager;
    explicit AbstractDatedDocument(int type)
        : AbstractDocument(type, true), birthDate(0) {}

    static time_t getDate(std::istream& is) {
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

    static void printTime(std::ostream& os, time_t time) {
        tm* date = localtime(&time);
        os << std::setw(2) << std::setfill('0') << date->tm_mday << "."
           << std::setw(2) << std::setfill('0') << date->tm_mon << "."
           << date->tm_year
           << " ";
    }


protected:
    time_t birthDate;
};

typedef std::shared_ptr<AbstractDocument> DocumentPointer;

struct AbstractDocumentCreator {
    explicit AbstractDocumentCreator(int t, const std::string n)
        : type(t), name(n) {}

    virtual DocumentPointer operator()() = 0;

    friend std::ostream& operator << (std::ostream& os, const AbstractDocumentCreator& obj) {
        return os << obj.type << ": " << obj.name;
    }

    int type;
    std::string name;
};

typedef std::shared_ptr<AbstractDocumentCreator> CreatorPointer;

#endif // DOCUMENT_H
