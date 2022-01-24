// needed for lab
// Mikhail Nesterenko
// 3/14/2016
// Modified by Brian Scalfano for Lab 9
// 10/31/21

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot{
public:
   CarLot();
   Car *testDriveCar(){return car4sale_[currentCar_];}

   // if a car is bought, requests a new one
   Car *buyCar(){ 
      Car *bought = car4sale_[currentCar_];
      car4sale_[currentCar_] = 
        factories_[rand()%factories_.size()]->requestCar();
      return bought;
   }

   Car* nextCar(){
      ++currentCar_;
      if(currentCar_ == lotSize_) currentCar_ = 0;
      return car4sale_[currentCar_];
   }

   int lotSize(){
      return lotSize_;
   }
		     
private:
   static const int lotSize_ = 10;
   Car *car4sale_[lotSize_]; // single car for sale at the lot
   int currentCar_;
   vector<CarFactory *> factories_;
};


CarLot::CarLot(){
   // creates 2 Ford factories and 2 Toyota factories 
   factories_.push_back(new FordFactory());   
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // gets the first car for sale
   for(int i = 0; i < lotSize_; ++i){
      car4sale_[i] = factories_[rand() % factories_.size()] -> requestCar();
   }
   
   currentCar_ = 0;
}



CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   bool carFound = false;
   auto preferredCar = new Toyota();



   for(int i = 0; i < carLotPtr->lotSize() && !carFound; ++i){
      Car *toBuy = carLotPtr -> testDriveCar();

      cout << "Buyer " << id << " ";
      cout << "test driving " 
      << toBuy->getMake() << " "
      << toBuy->getModel() << endl;

      if (toBuy->getModel() == preferredCar->getModel()){
      cout << "Buyer " << id << " loves the " << toBuy->getModel() << "! They are buying it!" << endl;
      carLotPtr -> buyCar();
      carFound = true;
      } 

      carLotPtr->nextCar();
   }


   if(!carFound){
      cout << "Buyer " << id << " did not like any of the cars." << endl;
   }
      
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   bool carFound = false;
   auto preferredCar = new Ford();



   for(int i = 0; i < carLotPtr->lotSize() && !carFound; ++i){
      Car *toBuy = carLotPtr -> testDriveCar();

      cout << "Buyer " << id << " ";
      cout << "test driving " 
      << toBuy->getMake() << " "
      << toBuy->getModel() << endl;

      if (toBuy->getModel() == preferredCar->getModel()){
      cout << "Buyer " << id << " loves the " << toBuy->getModel() << "! They are buying it!" << endl;
      carLotPtr -> buyCar();
      carFound = true;
      } 

      carLotPtr->nextCar();
   }


   if(!carFound){
      cout << "Buyer " << id << " did not like any of the cars." << endl;
   }
}



int main() {
   srand(time(nullptr));

   const int numBuyers=10;
   for(int i=0; i < numBuyers; ++i)
      if(rand()% 2 == 0)
	 toyotaLover(i);
      else
	 fordLover(i);
  
}