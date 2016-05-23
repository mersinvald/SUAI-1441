#ifndef PASSPORT_H
#define PASSPORT_H
#include "AbstractDocument.hpp"
#include <time.h>
#include <memory>

enum {
    DocType_ID = 1
};

class ID : public AbstractDatedDocument {
public:
    explicit ID(int type)
        : AbstractDatedDocument(type), fatherName(""), startDate(0) {}

    virtual void          promt();
    virtual std::ostream& write (std::ostream& os) const;
    virtual std::istream& read (std::istream& is);

protected:
    std::string fatherName;
    time_t      startDate;
};

class IDCreator : public AbstractDocumentCreator {
public:
    using AbstractDocumentCreator::AbstractDocumentCreator;
    static void Init();
    virtual DocumentPointer operator()();
};


#endif // PASSPORT_H
