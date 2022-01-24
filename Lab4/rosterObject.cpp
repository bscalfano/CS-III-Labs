// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018
// Updated by Brian Scalfano
// 9/27/2021

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string print() const {
      string nameAndClasses = firstName_ + ' ' + lastName_;
      //for(auto it = classes_.begin(); it != classes_.end(); ++it){
      for(auto it : classes_){
         nameAndClasses += ' ' + it;
      }
      return nameAndClasses;
    }

    string getFirst(){return firstName_;}
    string getLast(){return lastName_;}
    void addClass(string courseName){classes_.push_back(courseName);}

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
   list<string> classes_;   
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

    if (argc <= 1){ 
        cout << "usage: " << argv[0] 
        << " list of courses, dropouts last" << endl;
        exit(1);
    }


    list<Student> roster;
    for(int i=1; i < argc-1; ++i){
        readRoster(roster, argv[i]);   
    }

    printRoster(roster);
}


void readRoster(list<Student>& roster, string fileName){
    ifstream course(fileName);
    string courseName = fileName.substr(0,3);
    string first, last;
   
    while(course >> first >> last){
        bool nameFound = false;
        //int debugCounter = 0;
        for(auto it = roster.begin(); it != roster.end() && !nameFound; ++it){
            if(it->getFirst() == first && it->getLast() == last){
                nameFound = true;
                it->addClass(courseName);
            }
        }
      
        if(!nameFound){
            Student temp(first, last);
            temp.addClass(courseName);
            roster.push_back(temp);
        }

    }
    course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
    for(const auto& student : roster)
        cout << student.print() << endl;
}