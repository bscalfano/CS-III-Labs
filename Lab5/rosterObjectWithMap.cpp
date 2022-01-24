// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018
// Updated by Brian Scalfano for Lab 5
// 10/4/21

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;
using std::map;
using std::pair;
using std::make_pair;


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
   
  string print() const {return firstName_ + ' ' + lastName_;}

    string getFirst(){return firstName_;}
    string getLast(){return lastName_;}
    //void addClass(string courseName){classes_.push_back(courseName);}

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
   //list<string> classes_;   
};




// reading a list from a fileName
void readRoster(map<Student, list<string>>& roster, string fileName);  
// printing a list out
void printRoster(const map<Student, list<string>>& roster); 

int main(int argc, char* argv[]){

    if (argc <= 1){ 
        cout << "usage: " << argv[0] 
        << " list of courses, dropouts last" << endl;
        exit(1);
    }


    //list<Student> roster;
    map<Student, list<string>> roster;
    for(int i=1; i < argc-1; ++i){
        readRoster(roster, argv[i]);   
    }

    printRoster(roster);
}


void readRoster(map<Student, list<string>>& roster, string fileName){
    ifstream course(fileName);
    string courseName = fileName.substr(0,3);
    string first, last;
   
    while(course >> first >> last){
        //bool nameFound = false;
        //int debugCounter = 0;
        Student temp(first, last);

        if(roster.find(temp) != roster.end()){
            roster[temp].push_back(courseName);
        }
        else{
            list<string> tempCourses;
            tempCourses.push_back(courseName);
            roster.insert(make_pair(temp, tempCourses));
        }

        /*// LAB 4 LOGIC
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
        */
    }
    course.close();
}

// printing a list out
void printRoster(const map<Student, list<string>>& roster){
    for(const auto& stud : roster){
        cout << stud.first.print();
        for(const auto& course : stud.second){
            cout << ' ' << course;
        }
        cout << endl;
    }
}