// Brian Scalfano
// Lab 2 Function Definitions
// CS3 Section 003

#include <iostream>
#include <string>
#include <algorithm>
#include "WordList.hpp"

using std::cout;
using std::endl;
using std::string;
using std::sort;

// WordOccurrence Functions

WordOccurrence::WordOccurrence(const string& word, int num){  // Constructor
    word_ = word;
    num_ = num;
}

bool WordOccurrence::matchWord(const string &word){
    return word_ == word;
}

void WordOccurrence::increment(){
    ++num_;
}

string WordOccurrence::getWord() const{
    return word_;
}

int WordOccurrence::getNum() const{
    return num_;
}




// WordList Functions
WordList::WordList(int size){
    size_= size;
    wordArray_= (size > 0) ? new WordOccurrence[size] : nullptr;
}

WordList::WordList(const WordList &rhs){
    if(this != &rhs){
        size_ = rhs.size_;
        wordArray_ = new WordOccurrence[size_];
        for(int i = 0; i < size_; ++i){
            wordArray_[i] = rhs.wordArray_[i];
        }
    }
}

WordList::~WordList(){
    delete [] wordArray_;
}

WordList& WordList::operator=(WordList rhs){
    if(this != &rhs){
        size_ = rhs.size_;
        wordArray_ = new WordOccurrence[size_];
        for(int i = 0; i < size_; ++i){
            wordArray_[i] = rhs.wordArray_[i];
        }
    }

    return *this;
}

bool equal(const WordList &list1, const WordList &list2){
    if(list1.size_ != list2.size_){
        return false;
    }
    for(int i = 0; i < list1.size_; ++i){
        if(list1.wordArray_[i].getWord() != list2.wordArray_[i].getWord()) return false;
        if(list1.wordArray_[i].getNum() != list2.wordArray_[i].getNum()) return false;
    }
    return true;
}

void WordList::addWord(const string &word){

    //cout << "Word is: " << word << endl;
    bool foundWord = false;
    for(int i = 0; i < size_; ++i){
        //cout << "In for loop " << i << endl; 
        if(wordArray_[i].matchWord(word)){ 
            //cout << "Found matching word" << endl;
            wordArray_[i].increment();
            foundWord = true;
            break;
        }
    }


    
    if(!foundWord){
        //cout << "Word not found" << endl;
        ++size_;

        //CREATE NEW DYNAMIC ARRAY WITH SIZE
        WordOccurrence *temp = new WordOccurrence[size_];
        //cout << "New array created" << endl;
        //COPY ALL OF CLASS ARRAY INTO TEMP ARRAY
        for(int i = 0; i < size_ - 1; ++i){
            //cout << "In second for loooooop " << i << endl;
            temp[i] = wordArray_[i];
        }
        //cout << "Array copied" << endl;
        //ADD NEW WORD TO ARRAY
        WordOccurrence *tempWO = new WordOccurrence(word, 1);
        temp[size_ - 1] = *tempWO;
        //cout << "New word added: " << temp[size_ - 1].getWord() << endl;
        //CHANGE CLASS POINTER TO ADDRESS OF NEW ARRAY
        WordOccurrence *temp2 = wordArray_;
        wordArray_ = temp;
        //cout << "Pointers changed" << endl;
        //DELETE OLD ARRAY
        delete [] temp2;
        //cout << "Old array deleted" << endl;
    }
}

bool mySort(WordOccurrence& myWord1, WordOccurrence myWord2){
    return myWord1.getNum() < myWord2.getNum();
}

void WordList::print(){
    // SORT FOR RAREST WORDS FIRST
    sort(wordArray_, wordArray_ + size_, mySort);

    cout << "Word Counts" << endl;
    cout << "-----------" << endl;
    for(int i = 0; i < size_; ++i){
        cout << wordArray_[i].getWord() << ": " << wordArray_[i].getNum() << endl;
    }
}