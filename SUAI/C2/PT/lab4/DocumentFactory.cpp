#include "DocumentFactory.hpp"
#include <stdexcept>

std::map<int, CreatorPointer>
DocumentFactory::creatorMap;


const char*
TypeAlteadyRegisteredException::what() const noexcept {
    std::stringstream ss;
    ss << "Type " << type << " is already registered";
    return ss.str().c_str();
}

void
DocumentFactory::push(AbstractDocumentCreator* creator) {
    if(creatorMap.find(creator->type) != creatorMap.end()) {
        throw TypeAlteadyRegisteredException(creator->type);
    }

    creatorMap[creator->type] = CreatorPointer(creator);
}

AbstractDocumentCreator&
DocumentFactory::get(int type) {
    return *creatorMap[type];
}

DocumentPointer
DocumentFactory::create(int type) {
    return creatorMap[type]->operator()();
}

DocumentPointer
DocumentFactory::promt() {
    std::cout << "Availible document types:" << std::endl;
    for(auto& type : creatorMap) {
        auto& dt = *type.second.get();
        std::cout << dt.type << ": " << dt.name << std::endl;
    }

    int type;
    std::cout << "Select type: ";
    std::cin  >> type;

    auto doc = create(type);
    doc->promt();
    return doc;
}


