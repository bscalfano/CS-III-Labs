// Demonstrating state transitions for Lab 10
// Brian Scalfano
// 11/8/21

#include <string>

using std::string;

#ifndef STATE_TRANSITIONS
#define STATE_TRANSITIONS


class State;

class Process{
public:
    Process();
    void admitted();
	void schedulerDispatch();
	void eventCompletion();
	void interrupt();
	void eventWait();
	void exit();

    void changeState(State* myState){state_ = myState;}

    Process* clone(){return new Process();}

    string report();

    void setID(int id){processID_ = id;}

private:
    State* state_;
    int processID_;
};

class State{
public:
    virtual void admitted(Process*) {}
	virtual void interrupt(Process*) {}
	virtual void schedulerDispatch(Process*) {}
    virtual void eventWait(Process*) {}
	virtual void eventCompletion(Process*) {}
	virtual void exit(Process*) {}
    virtual string report() = 0;
    void changeState(Process* myProcess, State* myState){
        myProcess->changeState(myState);
    }
};



class New : public State{
public:
    static State* instance() {
		static State* onlyInstance = new New;
		return onlyInstance;
	}

    void admitted(Process* myProcess) override;

    string report() override {return "New";}
private:
    New(){}
    New(const New&) = delete;
    New& operator=(const New&) = delete;
};




class Ready : public State{
public:
    static State* instance() {
		static State* onlyInstance = new Ready;
		return onlyInstance;
	}

    void schedulerDispatch(Process* myProcess) override;

    string report() override {return "Ready";}
private:
    Ready(){}
    Ready(const Ready&) = delete;
    Ready& operator=(const Ready&) = delete;
};




class Running : public State{
public:
    static State* instance() {
		static State* onlyInstance = new Running;
		return onlyInstance;
	}

    void interrupt(Process*) override;
    void eventWait(Process*) override;
	void exit(Process*) override;

    string report() override {return "Running";}
private:
    Running(){}
    Running(const Running&) = delete;
    Running& operator=(const Running&) = delete;
};




class Waiting : public State{
public:
    static State* instance() {
		static State* onlyInstance = new Waiting;
		return onlyInstance;
	}

    void eventCompletion(Process*) override;

    string report() override {return "Waiting";}
private:
    Waiting(){}
    Waiting(const Waiting&) = delete;
    Waiting& operator=(const Waiting&) = delete;
};




class Terminated : public State{
public:
    static State* instance() {
		static State* onlyInstance = new Terminated;
		return onlyInstance;
	}

    string report() override {return "Terminated";}
private:
    Terminated(){}
    Terminated(const Terminated&) = delete;
    Terminated& operator=(const Terminated&) = delete;
};


#endif // STATE_TRANSITIONS