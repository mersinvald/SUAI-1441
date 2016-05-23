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

    friend std::ostream& operator<< (std::ostream& os, const AbstractDocument& obj);
    friend std::istream& operator>> (std::istream& is, AbstractDocument& obj);

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

    static time_t getDate(std::istream& is);
    static void printTime(std::ostream& os, time_t time);

protected:
    time_t birthDate;
};

typedef std::shared_ptr<AbstractDocument> DocumentPointer;

struct AbstractDocumentCreator {
    explicit AbstractDocumentCreator(int t, const std::string n)
        : type(t), name(n) {}

    virtual DocumentPointer operator()() = 0;

    int type;
    std::string name;
};

typedef std::shared_ptr<AbstractDocumentCreator> CreatorPointer;

#endif // DOCUMENT_H
