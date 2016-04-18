#include <iostream>
#include <string.hpp>

using namespace std;
using namespace msvd;

int main(int argc, char *argv[]) {
    String helloworld;
    String hello2;

    {
        String hello("Hello ");
        String world("World");

        hello2 = hello;

        helloworld = hello + world;
    }

    String str1;
    cin >> str1;

    String str2 = str1;
    String str3 = str2;
    String str4 = str1;
    String str5 = str1;
    String str6 = str5;

    hello2 = str4;

    cout << hello2 << endl << helloworld << endl << str3 << endl;
}
