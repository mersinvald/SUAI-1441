#include "ID.hpp"
#include "DocumentFactory.hpp"
#include <memory>

void
IDCreator::Init() {
    DocumentFactory::push(new IDCreator(DocType_ID, "Passport"));
}

DocumentPointer
IDCreator::operator()() {
    return DocumentPointer(new ID(type));
}

std::ostream&
ID::write(std::ostream& os) const {
    os << type << " "
       << name << " "
       << secondName << " "
       << fatherName << " ";
    ID::printTime(os, birthDate);
    ID::printTime(os, startDate);
    return os;
}

std::istream&
ID::read(std::istream& is) {
    is >> name
       >> secondName
       >> fatherName;
    birthDate = ID::getDate(is);
    startDate = ID::getDate(is);
    return is;
}

void
ID::promt() {
    std::cout << "Name:         ";
    std::cin  >> name;
    std::cout << "Second Name:  ";
    std::cin  >> secondName;
    std::cout << "Father Name:  ";
    std::cin  >> fatherName;
    std::cout << "Birth Date:   ";
    birthDate = ID::getDate(std::cin);
    std::cout << "Start Date:   ";
    startDate = ID::getDate(std::cin);
}
