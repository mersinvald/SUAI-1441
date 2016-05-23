#include "ID.hpp"
#include "documentfactory.hpp"
#include <memory>

IDCreator::Initializer IDCreator::initializer;
IDCreator::Initializer::Initializer() {
    DocumentFactory::push(new IDCreator(DocType_ID, "Passport"));
}

DocumentPointer
IDCreator::operator()() {
    return DocumentPointer(new ID(type));
}

std::ostream&
ID::write(std::ostream& os) const {
    return os << type << " "
              << name << " "
              << secondName << " "
              << fatherName << " "
              << birthDate << " "
              << startDate << " ";
}

std::istream&
ID::read(std::istream& is) {
    return is >> name
              >> secondName
              >> fatherName
              >> birthDate
              >> startDate;
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
