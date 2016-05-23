#include "internationalid.hpp"
#include "documentfactory.hpp"

void
InternationalIDCreator::Init() {
    DocumentFactory::push(new InternationalIDCreator(DocType_InternetionalID, "International Passport"));
}

DocumentPointer
InternationalIDCreator::operator()() {
    return DocumentPointer(new InternationalID(type));
}

std::ostream&
InternationalID::write(std::ostream& os) const {
    os << type << " "
       << name << " "
       << secondName << " ";
    InternationalID::printTime(os, birthDate);
    InternationalID::printTime(os, startDate);
    InternationalID::printTime(os, endDate);
    return os;
}

std::istream&
InternationalID::read(std::istream& is) {
    is >> name
       >> secondName;
    birthDate = InternationalID::getDate(is);
    startDate = InternationalID::getDate(is);
    endDate = InternationalID::getDate(is);
    return is;
}

void
InternationalID::promt() {
    std::cout << "Name:         ";
    std::cin  >> name;
    std::cout << "Second Name:  ";
    std::cin  >> secondName;
    std::cout << "Birth Date:   ";
    birthDate = InternationalID::getDate(std::cin);
    std::cout << "Start Date:   ";
    startDate = InternationalID::getDate(std::cin);
    std::cout << "End Date:     ";
    endDate = InternationalID::getDate(std::cin);
}
