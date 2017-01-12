#include <iostream>
#include "DocumentManager.hpp"
#include "ID.hpp"
#include "InternationalID.hpp"
#include "StudentID.hpp"

using namespace std;

int main() {
    IDCreator::Init();
    InternationalIDCreator::Init();
    StudentIDCreator::Init();
    DocumentManager docman;

    docman.promt();

    cout << "\nYou have " << docman.count() << " documents.\n";
    cout << "Your documents: ";
    docman.show();

    for(auto& type : DocumentFactory::creatorMap) {
        auto& doc = *type.second.get();
        cout << "You have " << docman.count(doc.type) << " documents of type " << doc.name << std::endl;
        cout << "Your documents of type " << doc.name << ":" << endl;
        docman.show(doc.type);
        cout << endl;
    }

    cout << "Enter date to search by: ";
    docman.show(AbstractDatedDocument::getDate(cin));

    std::cout << std::endl;

    std::string sname;
    cout << "Enter second name to search by: ";
    cin >> sname;
    docman.show(sname);

    cout << "Documents saved to file \"docs.txt\"\n";
    docman.save("docs.txt");

    for(auto& type : DocumentFactory::creatorMap) {
        auto& doc = *type.second.get();
        docman.del(doc.type);
        cout << "Deleting documents of type " << doc.name << ":" << endl;
        cout << "\nYou have " << docman.count() << " documents.\n";
        cout << endl;
    }

    cout << "Loading documents from file \"docs.txt\"\n";
    docman.load("docs.txt");

    cout << "\nYou have " << docman.count() << " documents.\n";
    cout << "Your documents: ";
    docman.show();

}
