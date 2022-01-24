#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::ifstream;
using std::to_string;

void printError(string, string, int, int, string, string);

int main(int argc, char **argv){

    // Alerts user that they used improper number of inputs
    if(argc != 3){
        cout << "Invalid amount of arguments" << endl;
        return 0;
    }

    // Prints the three inputs
    cout << "The number of arguments is " << argc << endl;
    for(int i = 0; i < argc; ++i){
        cout << "Argument " << i << ": " << argv[i] << endl;
    }

    // Declaring file variables
    ifstream myFile1;
    ifstream myFile2;

    // Initializing file variables
    myFile1.open(argv[1]);
    myFile2.open(argv[2]);


    // Declaring necessary variables
    //int currentChar = 0;
    //int charCount;
    int lineCount = 0;

    // Loops through each line
    while(!myFile1.eof() || !myFile2.eof()){
        ++lineCount;

	//cout << "In first loop " << lineCount << endl;

        // Creates temporary line variables
        string line1;
        string line2;

        // Gets lines from both files
        getline(myFile1, line1);
        getline(myFile2, line2);

        //cout << "Line 1 Length: " << line1.length() << endl << "Line 2 Length: " << line2.length() << endl;


        // Loops through each character
        bool mismatchFound = false;
        for(int j = 0; j < line1.length() && j < line2.length(); ++j){
	    //cout << "In second loop " << j << endl;

            // If the two characters do not match, prints message
            if(line1[j] != line2[j] && !mismatchFound){
                printError(line1, line2, lineCount, j, argv[1], argv[2]);
                mismatchFound = true;
            }
        }
    }


    // Closing file variables
    myFile1.close();
    myFile2.close();
    return 0;
}


// Prints an error message denoting that the two lines are not identical
void printError(string line1, string line2, int lineNum, int charPos, string file1, string file2){
    // Prints the first line
    cout << file1 << ": " << lineNum << ": " << line1 << endl;

    // Prints the second line
    cout << file2 << ": " << lineNum << ": " << line2 << endl;

    // Prints the number of spaces equal to the number of characters in the file name
    for(int k = 0; k < file2.length(); ++k){
        cout << " ";
    }

    cout << "  ";


    string lineNumString = to_string(lineNum);
    // Prints the number of spaces equal to the number of digits in the line number
    for(int k = 0; k < lineNumString.length(); ++k){
        cout << " ";
    }

    cout << "  ";

    // Prints the number of spaces equal to the amount of characters before a mismatch
    for(int k = 0; k < charPos; ++k){
        cout << " ";
    }

    cout << "^" << endl;
}
