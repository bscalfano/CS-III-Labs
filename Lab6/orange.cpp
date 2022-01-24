// sorting oranges
// converting vectors to multimaps
// Mikhail Nesterenko
// 2/17/2020
// Updated for Lab 6 by Brian Scalfano
// 10/4/21


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

struct Fruit{
   Variety v;
   string color; // red, green or orange
};


int main(){
   srand(time(nullptr));
   multimap<Variety, string> tree;

   int randSize = rand()%100+1;

   for(int i = 0; i < randSize; ++i){
      tree.emplace(static_cast<Variety>(rand() % 3), colors[rand()%3]);
   }
   /*
   for(auto f=tree.begin(); f!=tree.end(); ++f){
      
      f->v = static_cast<Variety>(rand() % 3);
      f->color = colors[rand()%3];
   }
      */
     
 
   cout << "Colors of the oranges: ";

   for(auto f=tree.lower_bound(Variety::orange); f!=tree.upper_bound(Variety::orange); ++f)
      cout << f->second << ", ";
      //if(f->first == Variety::orange) cout << f->second << ", ";
   cout << endl;

}
