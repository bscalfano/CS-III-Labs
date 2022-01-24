// Brian Scalfano
// Lab 3 Functions Header
// CS3 Section 003

#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <string>
#include <iostream>
#include "list.hpp"

using std::cout;
using std::endl;
using std::string;

template <typename T>
class Collection{
public:

  Collection(){first_ = nullptr;}

  void add(T);
  void remove(T);
  T last() const;
  void print() const;

  template <typename U>
  friend bool equal(const Collection<U>&, const Collection<U>&);

private:
    node<T>* first_;
};

template <typename T>
void Collection<T>::add(T myData){
    node<T>* tempPtr = new node<T>;
    tempPtr->setData(myData);
    if(this->first_ == nullptr){
        this->first_ = tempPtr;
    }
    else{
        node<T>* temp = this->first_;
        while(temp->getNext() != nullptr){
            temp = temp->getNext();
        }
        temp->setNext(tempPtr);
    }
}

template <typename T>
void Collection<T>::remove(T myData){
    node<T>* currNode = this->first_;
    node<T>* prevNode = nullptr;

    while(currNode != nullptr){
        if(currNode->getData() == myData && prevNode == nullptr){  // If data found, and is also the first item
            // Create a temporary node to prevent memory leak
            node<T>* tempPtr = currNode;

            // Set the first pointer to that of the next
            this->first_ = currNode->getNext();

            // Set the current node to the node after it
            currNode = currNode->getNext();

            // Delete the removed node
            delete tempPtr;
        }
        else if(currNode->getData() == myData){ // If data is found
            // Create a temporary node to prevent memory leak
            node<T>* tempPtr = currNode;

            // Set the pointer from the previous node to that of the next
            prevNode->setNext(currNode->getNext());

            // Set the current node to the node after it
            currNode = currNode->getNext();

            // Delete the removed node
            delete tempPtr;
        }
        else{
            prevNode = currNode;
            currNode = currNode->getNext();
        }
    }
}

template <typename T>
T Collection<T>::last() const{
    node<T>* temp = this->first_;
    while(temp->getNext() != nullptr){
        temp = temp->getNext();
    }
    return temp->getData();
}

template <typename T>
void Collection<T>::print() const{
    node<T>* temp = this->first_;
    while(temp->getNext() != nullptr){
        cout << temp->getData() << endl;
        temp = temp->getNext();
    }
    cout << temp->getData() << endl;
}

template <typename U>
bool equal(const Collection<U>& collection1, const Collection<U>& collection2){
    node<U>* temp1 = collection1.first_;
    node<U>* temp2 = collection2.first_;
    while(temp1->getNext() != nullptr || temp2->getNext() != nullptr){
        if(temp1->getData() != temp2->getData()){
            return false;
        }
        temp1 = temp1->getNext();
        temp2 = temp2->getNext();
    }
    return true;
}

#endif //COLLECTION_HPP