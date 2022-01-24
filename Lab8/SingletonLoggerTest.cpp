#include "SingletonLogger.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::getline;

int main(){
    string userInput;
    cout << "Enter something to be logged:\n";
    getline(cin, userInput);
    SingletonLogger::instance()->report("User input: ");
    SingletonLogger::instance()->report(userInput);
}