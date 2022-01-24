// Brian Scalfano
// Lab 2
// CS3 Section 003

#include <iostream>
#include <fstream>
#include <string>
#include "WordList.hpp"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::isalnum;

int main(int argc, char **argv){

    // Alerts user that they used an improper number of inputs
    if(argc != 2){
        cout << "Invalid amount of arguments" << endl;
        return 0;
    }

    // Prints the two inputs
    cout << "The number of arguments is " << argc << endl;
    for(int i = 0; i < argc; ++i){
        cout << "Argument " << i << ": " << argv[i] << endl;
    }

     // Declaring file variable
    ifstream myFile;
    //cout << "File declared" << endl;

    // Initializing file variables
    myFile.open(argv[1]);
    //cout << "File opened" << endl;

    // Declaring WordList variable
    WordList myList;
    //cout << "WordList declared" << endl;

    // Declaring string buffer outside of loop
    string wordBuf = "";
    //cout << "wordBuf declared" << endl;

    // Loop through each letter of the file
    while(!myFile.eof()){
        //cout << "In while loop" << endl;

        //Gets the next character and stores it in a buffer
        char charBuf = myFile.get();
        //cout << "Character: " << charBuf << endl;

        // If character is alphanumeric, add it to the word buffer
        if(isalnum(charBuf)){
            wordBuf += charBuf;
            //cout << "Char is alphanumeric" << endl;
        }

        // Else, add word to word list, reset the buffer
        else if(wordBuf != ""){
            //cout << "In else if" << endl;
            myList.addWord(wordBuf);
            wordBuf = "";
            //cout << "Char is not alphanumeric" << endl;
        }

    }

    // Print the results
    //cout << "Printing results" << endl;
    myList.print();
    //cout << "Results printed" << endl;

    myFile.close();
    //cout << "File closed" << endl;
}