#ifndef STUDENTID_H
#define STUDENTID_H
#include "AbstractDocument.hpp"

enum {
    DocType_StudentID = 3
};

class StudentID : public AbstractDocument {
public:
    explicit StudentID(int type)
        : AbstractDocument(type, false), universityName(""), groupNum(0) {}

    virtual void          promt();
    virtual std::ostream& write (std::ostream& os) const;
    virtual std::istream& read (std::istream& is);

protected:
    std::string universityName;
    int         groupNum;
};

struct StudentIDCreator : public AbstractDocumentCreator {
    using AbstractDocumentCreator::AbstractDocumentCreator;
    static void Init();
    virtual DocumentPointer operator()();
};

#endif // STUDENTID_H
