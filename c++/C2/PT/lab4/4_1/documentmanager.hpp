#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H
#include "document.hpp"
#include "documentfactory.hpp"
#include <string>
#include <list>
#include <memory>

class DocumentManager {
public:
    DocumentManager();

    void promt();

    void save(const std::string& filename) const;
    void load(const std::string& filename);

    void push(DocumentPointer doc);
    void push(AbstractDocument* docptr);
    void del(int type);

    uint count() const;
    uint count(int type) const;

    void show() const;
    void show(int type) const;
    void show(const std::string& sname) const;
    void show(time_t bd) const;

private:
    std::list<DocumentPointer> doclist;
};

#endif // DOCUMENTMANAGER_H
