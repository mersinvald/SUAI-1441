#include "StudentID.hpp"
#include "DocumentFactory.hpp"

void
StudentIDCreator::Init() {
    DocumentFactory::push(new StudentIDCreator(DocType_StudentID, "Student ID"));
}

DocumentPointer
StudentIDCreator::operator()() {
    return DocumentPointer(new StudentID(type));
}

std::ostream&
StudentID::write(std::ostream& os) const {
    return os << type << " "
              << name << " "
              << secondName << " "
              << universityName << " "
              << groupNum << " ";
}

std::istream&
StudentID::read (std::istream& is) {
    return is >> name
              >> secondName
              >> universityName
              >> groupNum;
}

void
StudentID::promt() {
    std::cout << "Name:         ";
    std::cin  >> name;
    std::cout << "Second Name:  ";
    std::cin  >> secondName;
    std::cout << "University:   ";
    std::cin  >> universityName;
    std::cout << "Group Number: ";
    std::cin  >> groupNum;
}
