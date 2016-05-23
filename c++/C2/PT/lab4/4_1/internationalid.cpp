#include "internationalid.hpp"
#include "documentfactory.hpp"

InternationalIDCreator::Initializer InternationalIDCreator::initializer;
InternationalIDCreator::Initializer::Initializer() {
    DocumentFactory::push(new InternationalIDCreator(DocType_InternetionalID, "International Passport"));
}

DocumentPointer
InternationalIDCreator::operator()() {
    return DocumentPointer(new InternationalID(type));
}

std::ostream&
InternationalID::write(std::ostream& os) const {
    return os << type << " "
              << name << " "
              << secondName << " "
              << birthDate << " "
              << startDate << " "
              << endDate << " ";
}

std::istream&
InternationalID::read(std::istream& is) {
    return is >> name
              >> secondName
              >> birthDate
              >> startDate
              >> endDate;
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
    startDate = InternationalID::getDate(std::cin);
}
