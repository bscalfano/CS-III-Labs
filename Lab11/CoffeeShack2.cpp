// Brian Scalfano
// Lab 11 Part 2
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

    bool prepareDrink(){
        if(!customers_.empty()){
            Customer *c = *(customers_.begin());
            cout << "[*] Preparing drink for " << c->getName() << endl;
            notifyCustomers(c->getDrink());
            deregisterCustomer(c);
            delete c;
            cout << "[*] " << customers_.size() << " customers waiting. " << endl;
            return true;
        }
        else{
            return false;
        }
    }
private:
    unordered_set<Customer*> customers_;
};

int main(){
    Barista barista;

    while(true){
        if(rand() % 2 == 0){
            Customer *c = new Customer();
            barista.takeOrder(c);
        }
        else{
            barista.prepareDrink();
        }
    }

    return 0;
}