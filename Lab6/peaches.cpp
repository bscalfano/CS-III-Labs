// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 9/30/2021
// Updated for Lab 6 by Brian Scalfano
// 10/4/21


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using std::generate;
using std::remove_copy_if;
using std::remove_if;
using std::advance;
using std::count_if;
using std::accumulate;

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   /*for(auto it = basket.begin(); it != basket.end(); ++it){
      it->weight = minWeight + 
	           static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      it->ripe = rand() % 2;
   }*/

   generate(basket.begin(), basket.end(), [=](){
      Peaches myPeach;
      myPeach.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      myPeach.ripe = (rand() % 2 == 1) ? true : false;
      return myPeach;
   });


   
   // for_each() possibly
   /*cout << "all peaches"<< endl;
   for(const auto &e: basket) {
      e.print(); 
   }*/

   cout << "all peaches" << endl;
   for_each(basket.begin(), basket.end(), [=](Peaches myPeach){myPeach.print();});

   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   /*deque<Peaches> peck;
   for(auto it=basket.begin(); it != basket.end();)
      if(it->ripe){
	 peck.push_front(std::move(*it));
	 it=basket.erase(it);
      }else
	 ++it;*/

   deque<Peaches> peck;
   remove_copy_if(basket.begin(), basket.end(), front_inserter(peck), [=](Peaches myPeach){return !myPeach.ripe;});
   basket.erase(remove_if(basket.begin(), basket.end(), [=](Peaches myPeach) {return myPeach.ripe;}), basket.end());

   // for_each() possibly
   /*cout << "peaches remainng in the basket"<< endl;
   for(const auto &e: basket) {
      e.print(); 
   }*/
   cout << "peaches remaining in the basket"<< endl;
   for_each(basket.begin(), basket.end(), [=](Peaches myPeach){myPeach.print();});

   cout << endl;

   // for_each() possibly
   /*cout << "peaches moved to the peck"<< endl;
   for(const auto &e: peck) {
      e.print();
   }*/
   cout << "peaches moved to the peck"<< endl;
   for_each(peck.begin(), peck.end(), [=](Peaches myPeach){myPeach.print();});


   // prints every "space" peach in the peck
   // 
   const int space=3; 
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no iterator arithmetic
   /*auto it=peck.cbegin(); int i = 0;   
   while(it != peck.cend()){
      if(i == space){
	      it->print();
	      i=0;
      }
      ++i; 
      ++it;
   }*/
   auto it = peck.begin();
   advance(it, 2);
	while (it < peck.end()) {
      it->print();
      advance(it, space);
	}


   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   /*const double weightToJam = 10.0;
   double jamWeight = 0; 
   for(auto it=peck.begin(); it != peck.end();)
      if(it->weight < weightToJam){
	 jamWeight += it->weight;
	 it=peck.erase(it);
      }else
	 ++it;

   cout << "Weight of jam is: " << jamWeight << endl;*/

   const double weightToJam = 10.0;
   double jamWeight = accumulate(peck.begin(), peck.end(), 0.0, [=] (double sum, Peaches myPeach) {
       if (myPeach.weight < weightToJam){
          return sum + myPeach.weight;
       }
      else{
         return sum;
      }
   });
   peck.erase(remove_if(peck.begin(), peck.end(), [=](Peaches myPeaches){return myPeaches.weight < weightToJam;}));

   cout << "Weight of jam is: " << jamWeight << endl;
}