// Brian Scalfano
// Lab 11 Part 3
// 11/15/21

#include <iostream>
#include <unordered_set>
#include "drink.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unordered_set;

class Customer{
public:
    Customer(string custName) : name_(custName){}
    void notify(Drink *d) const{
        if(d == drink_){
            cout << "[*] " << name_ << " got a " << drink_->getName() << " which costs $" << drink_->getPrice() << endl;
        }
    }

    const string &getName() const{
        return name_;
    }

    void setName(const string &name){
        name_ = name;
    }

    Drink *getDrink() const{
        return drink_;
    }

    void setDrink(Drink *drink){
        drink_ = drink;
    }

private:
    Drink* drink_;
    string name_;
};



class Barista{
public:
    Barista(Barista *successor = nullptr): successor_(successor){}
    void registerCustomer(Customer *c){
        customers_.insert(c);
    }

    void deregisterCustomer(Customer *c){
        customers_.erase(c);
    }

    void notifyCustomers(Drink *ready){
        for(auto c : customers_){
            c->notify(ready);
        }
    }

    void takeOrder(Customer *c){
        cout << "Welcome to The Coffee Shack, would you like a coffee? [y/n] ";
        char wantCoffee;
        cin >> wantCoffee;
        if(wantCoffee == 'y'){
            cout << "Can I get you a [l]arge, [m]edium, or [s]mall coffee? ";
            char coffeeSize;
            cin >> coffeeSize;

            Drink *myDrink;

            switch(coffeeSize){
                case 's':
                    myDrink = new Coffee(DrinkType::small);
                    break;
                case 'm':
                    myDrink = new Coffee(DrinkType::medium);
                    break;
                case 'l':
                    myDrink = new Coffee(DrinkType::large);
                    break;
                default:
                    myDrink = new Coffee(DrinkType::small);
            }

            char toppingChar = '0';

            while(toppingChar != 'n'){
                cout << "Would you like to add [s]prinkles, [f]oam, or [n]ot? ";
                cin >> toppingChar;
                if(toppingChar == 's'){
                    myDrink = new Sprinkles(myDrink);
                }
                else if(toppingChar == 'f'){
                    myDrink = new Foam(myDrink);
                }
            }

            string custName;
            cout << "Can I get your name? ";
            cin >> custName;

            c->setName(custName);
            c->setDrink(myDrink);

            registerCustomer(c);

            cout << endl;
            cout << "[*] " << customers_.size() << " customers waiting. " << endl;
        }
    }

    void takeOrder(Customer *c, Drink *d){
        c->setDrink(d);

        registerCustomer(c);

        cout << "[*] " << c->getName() << " wants a " << d->getName() << endl;
        cout << "[*] " << customers_.size() << " customers waiting. " << endl << endl;
    }

    bool prepareDrink(){
        if(!customers_.empty()){
            Customer *c = *(customers_.begin());
            cout << "[*] Preparing drink for " << c->getName() << endl;
            handleDrink(c->getDrink());
            deregisterCustomer(c);
            delete c;
            cout << "[*] " << customers_.size() << " customers waiting. " << endl << endl;
            return true;
        }
        else{
            return false;
        }
    }

    virtual void handleDrink(Drink *myDrink){
        if(successor_ != nullptr){
            successor_->handleDrink(myDrink);
        }
        else{
            cout << "[*] Nobody can make this coffee" << endl;
        }
    }

private:
    static unordered_set<Customer*> customers_;
    Barista *successor_;
};




class JuniorBarista : public Barista{
public:
    JuniorBarista(Barista *successor = nullptr) : Barista(successor){}
    void handleDrink(Drink *myDrink) override{
        if(!myDrink->hasFoam() && !myDrink->hasSprinkles()){
            cout << "[*] Junior barista has made the drink" << endl;
            notifyCustomers(myDrink);
        }
        else{
            Barista::handleDrink(myDrink);
        }
    }
};




class SeniorBarista : public Barista{
public:
    SeniorBarista(Barista *successor = nullptr) : Barista(successor){}
    void handleDrink(Drink *myDrink) override{
        if(!myDrink->hasFoam()){
            cout << "[*] Senior barista has made the drink" << endl;
            notifyCustomers(myDrink);
        }
        else{
            Barista::handleDrink(myDrink);
        }
    }
};




class Manager : public Barista{
public:
    Manager(Barista *successor = nullptr) : Barista(successor){}
    void handleDrink(Drink *myDrink) override{
        cout << "[*] Manager has made the drink" << endl;
        notifyCustomers(myDrink);
    }
};




unordered_set<Customer*> Barista::customers_;
int main(){
    Barista *barista = new JuniorBarista(new SeniorBarista(new Manager()));

    Customer *c1 = new Customer("Alison");
    Customer *c2 = new Customer("Brian");
    Customer *c3 = new Customer("Carolyn");

    Drink *d1 = new Coffee(DrinkType::small);
    Drink *d2 = new Sprinkles(new Coffee(DrinkType::large));
    Drink *d3 = new Foam(new Sprinkles(new Coffee(DrinkType::medium)));

    barista->takeOrder(c1, d1);
    barista->takeOrder(c2, d2);
    barista->takeOrder(c3, d3);

    barista->prepareDrink();
    barista->prepareDrink();
    barista->prepareDrink();
}