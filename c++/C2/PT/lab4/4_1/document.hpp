#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>
#include <iostream>
#include <memory>
#include <cstdlib>

class AbstractDocument {
public:
    friend class DocumentManager;

    explicit AbstractDocument(int type, bool dated)
        : type(type), dated(false), name(""), secondName("") {}

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
        tm date = {};
        std::string s;
        for(int i = 0; i < 3; i++) {
            getline(is, s, '.');
            switch(i) {
            case 0: date.tm_mday = std::stoi(s); break;
            case 1: date.tm_mon  = std::stoi(s); break;
            case 2: date.tm_year = std::stoi(s); break;
            }
        }
        return timelocal(&date);
    }

    static void printTime(std::ostream& os, time_t time) {
        tm* date = localtime(&time);
        os << date->tm_mday << "." << date->tm_mon << "." << date->tm_year;
    }


protected:
    time_t birthDate;
};

typedef std::unique_ptr<AbstractDocument> DocumentPointer;

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

typedef std::unique_ptr<AbstractDocumentCreator> CreatorPointer;

#endif // DOCUMENT_H
