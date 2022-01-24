// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// 11/15/2016
// Used by Brian Scalfano for lab 11
// 11/15/21

#include <string>

using std::string;

enum class DrinkType {small, medium, large};

class Drink{
public:
   Drink():hasSprinkles_(false), hasFoam_(false){}
   virtual double getPrice() const = 0;
   virtual string getName() const = 0;
   void setHasSprinkles(bool myBool){
      hasSprinkles_ = myBool;
   }
   void setHasFoam(bool myBool){
      hasFoam_ = myBool;
   }
   bool hasSprinkles(){
      return hasSprinkles_;
   }
   bool hasFoam(){
      return hasFoam_;
   }
private: 
   bool hasSprinkles_;
   bool hasFoam_;
};



class Coffee : public Drink{
public:
   Coffee(const DrinkType type=DrinkType::small): type_(type){
      switch(type){
         case DrinkType::small:
            price_ = 1.00;
            name_ = "small coffee";
            break;
         case DrinkType::medium:
            price_ = 2.00;
            name_ = "medium coffee";
            break;
         case DrinkType::large:
            price_ = 3.00;
            name_ = "large coffee";
            break;
         default:
            price_ = 1.0;
            name_ = "small coffee";
      }
   }

      double getPrice() const override{
         return price_;
      }

      string getName() const override{
         return name_ + " with ";
      }

private:
   DrinkType type_;
   double price_;
   string name_;
};




class Sprinkles : public Drink{
public:
   Sprinkles(Drink *wrapped) : wrapped_(wrapped){
      setHasSprinkles(true);
   }
   double getPrice() const override{
      return wrapped_->getPrice() + 0.50;
   }
   string getName() const override{
      return wrapped_->getName() + "sprinkles, ";
   }
private:
   Drink *wrapped_;
};




class Foam : public Drink{
public:
   Foam(Drink *wrapped) : wrapped_(wrapped){
      setHasFoam(true);
   }
   double getPrice() const override{
      return wrapped_->getPrice() + 0.40;
   }
   string getName() const override{
      return wrapped_->getName() + "foam, ";
   }
private:
   Drink *wrapped_;
};