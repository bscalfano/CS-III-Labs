// Brian Scalfano
// Lab 2 Functions Header
// CS3 Section 003

#ifndef LAB_2_FUNCTIONS
#define LAB_2_FUNCTIONS

#include <string>


using std::string;

class WordOccurrence {
public:
    WordOccurrence(const string& word="", int num=0);
    bool matchWord(const string &); // returns true if word matches stored
    void increment(); // increments number of occurrences
    string getWord() const; 
    int getNum() const;

private:
    string word_;
    int num_;
};

class WordList{
public:
    // add copy constructor, destructor, overloaded assignment
    WordList(int size=0); //Default Constructor
    WordList(const WordList &obj); // Copy Constructor
    ~WordList(); // Destructor
    WordList& operator=(WordList); // Assignment Operator Overload

    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);

    void addWord(const string &);
    void print();
private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};

#endif //LAB_2_FUNCTIONS