// Brian Scalfano
// Lab 8 Singleton Logger
// 10/22/2021

#include <iostream>
#include <fstream>
#include <string>

using std::fstream;
using std::string;

class SingletonLogger
{
public:
    static SingletonLogger* instance(){
        static SingletonLogger myLogger;
        return &myLogger;
    }
    ~SingletonLogger(){
        myFile.close();
    };
    void report(const string& newRep){
        myFile << newRep << "\n";
    }
private:
    fstream myFile;

    SingletonLogger(){
        myFile.open("log.txt");
    };

    SingletonLogger(const SingletonLogger&) = delete;
    SingletonLogger& operator=(const SingletonLogger&) = delete;
};
