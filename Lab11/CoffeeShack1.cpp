// Brian Scalfano
// Lab 11 Part 1
// 11/15/21

#include <iostream>
#include "drink.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){
    cout << "Welcome to The Coffee Shack, can I get you a [l]arge, [m]edium, or [s]mall coffee? ";
    char coffeeSize;
    cin >> coffeeSize;

    Drink* myDrink;

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

    cout << endl << custName << ", your " << myDrink->getName() << "is ready. It will be $" << myDrink->getPrice() << ", please." << endl;
        
    return 0;
}