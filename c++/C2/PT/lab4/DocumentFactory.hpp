#ifndef DOCUMENTFABRIC_H
#define DOCUMENTFABRIC_H
#include "AbstractDocument.hpp"
#include <sstream>
#include <map>
#include <exception>
#include <memory>

struct TypeAlteadyRegisteredException : public std::exception {
    TypeAlteadyRegisteredException(int t) : type(t) {}
    virtual const char* what() const noexcept;
private:
    int type;
};

class DocumentFactory {
public:
    static void                     push(AbstractDocumentCreator* creator);
    static AbstractDocumentCreator& get(int type);
    static DocumentPointer          create(int type);
    static DocumentPointer          promt();

    static std::map<int, CreatorPointer> creatorMap;
};

#endif // DOCUMENTFABRIC_H
