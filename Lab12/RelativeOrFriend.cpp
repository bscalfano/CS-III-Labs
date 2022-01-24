// traversing genealogical tree using Composite and Visitors
// Mikhail Nesterenko
// 10/28/2015

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::cin; using std::endl;
using std::string; 
using std::vector;

class Person{ // component
public:
   Person(string firstName, Person *spouse, Person *father, Person *mother):
      firstName_(firstName), spouse_(spouse), father_(father), mother_(mother){}
   const string & getFirstName(){return firstName_;}
   Person *getSpouse(){return spouse_;}
   void setSpouse(Person *spouse){spouse_=spouse;}
   Person *getFather(){return father_;}
   Person *getMother(){return mother_;}

   bool isRelated(Person*);
   bool isSelf(Person*);
   bool isSibling(Person*);
   bool isParent(Person*);
   bool isChild(Person*);
   bool isAuntUncle(Person*);

   virtual void accept(class PersonVisitor *)=0;  
   virtual ~Person(){}
private:
   const string firstName_;
   Person *spouse_;
   Person *father_;
   Person *mother_;
};

bool Person::isRelated(Person *p) {
    if(isSelf(p)){
        return true;
    }
    else if(isSibling(p)){
        return true;
    }
    else if(isParent(p)){
        return true;
    }
    else if(isChild(p)){
        return true;
    }
    else if(isAuntUncle(p)){
        return true;
    }
    else{
        return false;
    }
}


bool Person::isSelf(Person* p){
    return (this == p);
}


bool Person::isSibling(Person* p){
    return (getFather() == p->getFather());
}


bool Person::isParent(Person* p){
    return (getFather() == p || getMother() == p);
}


bool Person::isChild(Person* p){
    return (this == p->getFather() || this == p->getMother());
}


bool Person::isAuntUncle(Person* p){
    Person* myFather = getFather();
    Person* myMother = getMother();

    if(myFather == nullptr || myMother == nullptr || p == nullptr){
        return false;
    }

    if(myFather->isSibling(p) || myMother->isSibling(p)){
        return true;
    }

    return false;
}


// leaf
// man has a last name 
class Man: public Person{
public:
   Man(string lastName, string firstName, Person *spouse, 
       Person *father, Person *mother): 
      lastName_(lastName), 
      Person(firstName, spouse, father, mother){}
   const string & getLastName(){return lastName_;}
   void accept(class PersonVisitor *visitor) override;
private:
   const string lastName_;
};

// composite
// woman has a list of children
class Woman: public Person{
public: 
   Woman(vector<Person *> children, 
       string firstName, 
       Person *spouse, 
       Person *father, Person *mother): 
       children_(children),
       Person(firstName, spouse, father, mother){}
   const vector<Person *> & getChildren() {return children_;}
   void setChildren(const vector<Person *> &children){ children_ = children;}
   void accept(class PersonVisitor *visitor) override;
private:
   vector<Person *> children_;
}; 

// abstract visitor
class PersonVisitor{
public:
   virtual void visit(Man*)=0;
   virtual void visit(Woman*)=0;
   virtual ~PersonVisitor(){}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor) {
    visitor->visit(this);
}

void Woman::accept(PersonVisitor *visitor){ 
   // children traversal through mother only
   // father's children are not traversed so as not 
   // to traverse them twice: for mother and father

   visitor->visit(this);
   // traversing descendants
   for(auto child : children_) 
      child->accept(visitor);   
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter: public PersonVisitor{
public:
   void visit(Man *m) override {
      cout << m->getFirstName() << " " << m->getLastName() << endl;
   }
   void visit(Woman *w) override {
      cout << w->getFirstName() << " ";
      if (w->getSpouse() != nullptr)
	 cout << static_cast<Man *>(w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
	 cout << static_cast<Man *> (w->getFather())->getLastName();
      else
	 cout << "Doe";
      cout << endl;
   }
};


class ChildrenPrinter: public PersonVisitor{
public:
   void visit(Man *m) override {
      cout << m->getFirstName() << ": ";
      Woman *spouse = static_cast<Woman *>(m->getSpouse());
      if(spouse != nullptr)
	 printNames(spouse->getChildren());
      cout << endl;
   }
   void visit(Woman *w) override {
      cout << w->getFirstName() << ": ";
      printNames(w->getChildren());
      cout << endl;
   }
private:
   void printNames(const vector<Person *> &children){
      for(const auto c: children)
	 cout << c->getFirstName() << ", ";
   }
};

class PersonFinder: public PersonVisitor {
public:
    PersonFinder(string firstName, string lastName):
    firstName_(firstName),
    lastName_(lastName),
    thisPerson(nullptr) {}

    void visit(Man *m) override {
        if (m->getFirstName() == firstName_ && m->getLastName() == lastName_)
        thisPerson = m;
    }

    void visit(Woman *w) override {
        string tempLastName = "";
        if (w->getFirstName() == firstName_) {
            if (w->getSpouse() != nullptr)
                tempLastName = static_cast<Man*>(w->getSpouse())->getLastName();
            else if (w->getFather() != nullptr)
                tempLastName = static_cast<Man*>(w->getFather())->getLastName();
            else
                tempLastName = "Doe";
        }
        if (tempLastName == lastName_) {
            thisPerson = w;
        }
    }
  
    Person* getThisPerson() {
        return thisPerson;
    }
 
private:
    const string firstName_;
    const string lastName_;
    Person *thisPerson;
};


// demonstrating the operation
int main(){

    // setting up the genealogical tree      
    // the tree is as follows
    //    
    //
    //       James Smith  <--spouse-->   Mary 
    //	                                  |
    //	                                 children -------------------------
    //	                                  |              |                |
    //	                                  |              |                |
    //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
    //	                                  |
    //	                                 children------------
    //	                                  |                 |
    //                                     |                 |
    //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
    //	       |
    //	     children
    //	       |
    //          |
    //	     Susan


    // first generation
    Man *js = new Man("Smith", "James", nullptr, nullptr, nullptr);
    Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
    ms->setSpouse(js); js->setSpouse(ms);

    // second generation
    Woman *ps = new Woman({}, "Patricia",  nullptr, js, ms);
    Man *wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
    ps->setSpouse(wj); wj->setSpouse(ps);

    vector<Person *> marysKids  = {ps,
                        new Man("Smith", "Robert", nullptr, js, ms),
                        new Woman({}, "Linda", nullptr, js, ms)};
    ms->setChildren(marysKids);

    // third generation
    Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
    vector<Person *> patsKids   = {mj, new Woman({}, "Barbara", nullptr, wj, ps)}; 
    ps->setChildren(patsKids);

    Woman *jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
    vector<Person *> jensKids = {new Woman({}, "Susan", nullptr, mj ,jj)};

    jj->setSpouse(mj); mj->setSpouse(jj);
    jj->setChildren(jensKids);
    

    // defining two visitors
    ChildrenPrinter *cp = new ChildrenPrinter;
    NamePrinter *np = new NamePrinter;

    // executing the traversal with the composite
    // and the specific visitor

    cout << "\nNAME LIST\n";
    ms->accept(np);
    cout << endl << endl;

    cout << "CHILDREN LIST\n";
    ms->accept(cp);

    
    cout << "\nJAMES' CHILDREN\n";
    js->accept(cp);


    while(true){
        string p1fn, p1ln;
        string p2fn, p2ln;

        cout << "Determine if two individuals are related." << endl 
        << "Enter first candidate: ";

        cin >> p1fn >> p1ln;

        cout << "Enter second candidate: ";

        cin >> p2fn >> p2ln;

        //cout << "Name 1: " << p1fn << " " << p1ln << ", Name 2: " << p2fn << " " << p2ln << endl;

        PersonFinder* finder1 = new PersonFinder(p1fn, p1ln);
        ms->accept(finder1);
        Person* p1 = finder1->getThisPerson();
            
        PersonFinder* finder2 = new PersonFinder(p2fn, p2ln);
        ms->accept(finder2);
        Person* p2 = finder2->getThisPerson();


        if(p1 != nullptr && p2 != nullptr){
            if(p1->isRelated(p2)){
                cout << "They are related." << endl;
            }
            else{
                cout << "They are just friends." << endl;
            }
        }
        else{
            cout << "They are just friends." << endl;
        }
    }

}