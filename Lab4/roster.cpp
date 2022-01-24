// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014
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

// reading a list from a fileName
void readRoster(list<list<string>>& roster, string fileName);  

// printing a list out
void printRoster(const list<list<string>>& roster); 

int main(int argc, char* argv[]){
   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl; exit(1);
   }
   
   
   list<list<string>> roster;
   for(int i = 0; i < argc -1; ++i){
      readRoster(roster, argv[i]);
   }

   printRoster(roster);
   
}

// reading in a file of names into a list of strings
void readRoster(list<list<string>>& roster, string fileName){
   ifstream course(fileName);
   string courseName = fileName.substr(0,3);
   string first, last;
   
   while(course >> first >> last){
      string fullName = first + ' ' + last;
      bool nameFound = false;
      for(auto it = roster.begin(); it != roster.end() && !nameFound; ++it){
         if(it->front() == fullName){
            nameFound = true;
            it->push_back(courseName);
         }
      }
      
      if(!nameFound){
         //ADD NAME AND COURSE
         list<string> temp;
         temp.push_back(fullName);
         temp.push_back(courseName);
         roster.push_back(temp);
      }

   }
   course.close();
}

// printing a list out
void printRoster(const list<list<string>>& roster){
   for(const auto& lst : roster){
      for(const auto& str: lst){
         cout << str << " ";
      }
      cout << endl;
   }
}