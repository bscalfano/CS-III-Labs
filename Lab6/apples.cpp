// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 09/30/2021
// Updated for Lab 6 by Brian Scalfano
// 10/4/21


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using std::generate;
using std::for_each;
using std::count_if;
using std::max_element;
using std::accumulate;
using std::transform;
using std::remove_if;
using std::sort;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};


int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   // assign random weight and color to apples in the crate
   // replace with generate()

   /*for(auto it = crate.begin(); it != crate.end(); ++it){
      it->weight = minWeight + 
	           static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      it->color = rand() % 2 == 1 ? "green" : "red";
   }*/

   

   generate(crate.begin(), crate.end(), [=](){
      Apples myApple;
      myApple.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      myApple.color = rand() % 2 == 1 ? "green" : "red";
      return myApple;
   });


    // for_each() possibly
   cout << "all apples"<< endl;
   /*for(const auto &e: crate) {
      e.print();
   }*/

   for_each(crate.begin(), crate.end(), [=](Apples myApple){myApple.print();});




   
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   // count_if()
   /*int cnt = 0;
   for(auto it = crate.cbegin(); it != crate.cend(); ++it) 
      if(it->weight > toFind) ++cnt;
   */

   int cnt = count_if(crate.begin(), crate.end(), [=](Apples myApple){return myApple.weight > toFind;});
   cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz" <<  endl;

   


   // find_if()
   /*cout << "at positions ";
   for(int i=0; i < size; ++i)
      if(crate[i].weight > toFind)
	 cout << i << ", ";
   cout << endl;*/

   auto it = crate.begin();

   while(it !=crate.end()){
      it = find_if(++it, crate.end(), [=](Apples myApple){return myApple.weight > toFind;});
      cout << it - crate.begin() << ", ";
   }

   


   // max_element()
   /*double heaviest = crate[0].weight;
   for(int i=1; i < size; ++i)
      if(crate[i].weight > heaviest) heaviest = crate[i].weight; 
   cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;*/

   auto heaviest = max_element(crate.begin(), crate.end(), [=](Apples myApple1, Apples myApple2){return myApple1.weight < myApple2.weight;});
   cout << "Heaviest apple weighs: " << heaviest->weight << " oz" << endl;



   // for_each() or accumulate()
   /*double sum = 0;
   for(int i=0; i < size; ++i)
      sum += crate[i].weight;
   cout << "Total apple weight is: " << sum << " oz" << endl;*/

   double sum = 0;
   for_each(crate.begin(), crate.end(), [&](Apples myApple){sum += myApple.weight;});
   cout << "Total apple weight is: " << sum << " oz" << endl;


   // transform();
   /*cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   for(int i=0; i < crate.size(); ++i)
      crate[i].weight += toGrow;*/

   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   transform(crate.begin(), crate.end(), crate.begin(), [=](Apples myApple){
      Apples temp;
      temp.color = myApple.color;
      temp.weight = myApple.weight + toGrow;
      return temp;
      });

   // remove_if()
   /*cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;
   
   for(auto it=crate.begin(); it != crate.end(); )
      if(it->weight < minAccept)
	 it = crate.erase(it);
      else
	 ++it;
	 
   cout << "removed " << size - crate.size() << " elements" << endl;*/

   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;

   int beforeRemoval = crate.size();
   crate.erase(remove_if(crate.begin(), crate.end(), [=](Apples myApple){return myApple.weight <= minAccept;}), crate.end());
   cout << "removed " << beforeRemoval - crate.size() << " elements" << endl;


   // bubble sort, replace with sort()
   /*bool swapped;
   do{
      swapped = false;
      for(int i=0; i < crate.size()-1; ++i)
	 if(crate[i].weight > crate[i+1].weight){
	    std::swap(crate[i], crate[i+1]);
	    swapped = true;
	 }
   }while(swapped);*/

   sort(crate.begin(), crate.end(), [=](Apples myApple1, Apples myApple2){return myApple1.weight < myApple2.weight;});


   // for_each() possibly
   /*cout << "sorted remaining apples"<< endl;
   for(const auto &e: crate) {
      e.print();
   }*/

   for_each(crate.begin(), crate.end(), [=](Apples myApple){myApple.print();});

}
