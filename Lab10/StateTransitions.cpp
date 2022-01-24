// Demonstrating state transitions for Lab 10
// Brian Scalfano
// 11/8/21

#include "StateTransitions.hpp"

#include <deque>
#include <cstdlib>
#include <time.h>
#include <iostream>

using std::deque; using std::cout; using std::endl; using std::to_string;

// State Functions

void New::admitted(Process* myProcess){
    changeState(myProcess, Ready::instance());
}

void Ready::schedulerDispatch(Process* myProcess){
    changeState(myProcess, Running::instance());
}

void Running::interrupt(Process* myProcess){
    changeState(myProcess, Ready::instance());
}

void Running::eventWait(Process* myProcess){
    changeState(myProcess, Waiting::instance());
}

void Running::exit(Process* myProcess){
    changeState(myProcess, Terminated::instance());
}

void Waiting::eventCompletion(Process* myProcess){
    changeState(myProcess, Ready::instance());
}



// Process Functions

Process::Process(){
    state_ = New::instance();
}

void Process::admitted(){
    state_->admitted(this);
}

void Process::schedulerDispatch(){
    state_->schedulerDispatch(this);
}

void Process::eventCompletion(){
    state_->eventCompletion(this);
}

void Process::interrupt(){
    state_->interrupt(this);
}

void Process::eventWait(){
    state_->eventWait(this);
}

void Process::exit(){
    state_->exit(this);
}

string Process::report(){
    string reportStr;
    reportStr += "Process ";
    reportStr += to_string(processID_);
    reportStr += " is in state ";
    reportStr += state_->report();
    return reportStr;
}


int main() {
	srand(time(nullptr));
	deque<Process*> waitingDeque;
	deque<Process*> readyDeque;

	Process processPrototype;

	for (int i = 0; i < 4; ++i) {
		readyDeque.push_back(processPrototype.clone());
	}

	//setting id
	for (int i = 0; i < readyDeque.size(); ++i) {
		readyDeque[i]->setID(i + 1);
	}

	// setting all 4 processes to ready 
	for (int i = 0; i < readyDeque.size(); ++i) {
		cout << readyDeque[i]->report() << endl;

		readyDeque[i]->admitted();

		cout << readyDeque[i]->report() << endl;

	}


	int running, waiting;

	while (!readyDeque.empty() || !waitingDeque.empty()) {
		running = (rand() % 3) + 1;
		waiting = (rand() % 2) + 1;

		if (!readyDeque.empty()) {
			readyDeque.front()->schedulerDispatch(); //calls on head
			cout << readyDeque.front()->report() << endl;
		}

		switch(running) {

			case(1): { // Process terminated

				if (!readyDeque.empty()) {
					readyDeque.front()->exit(); // Terminates process
                    cout << readyDeque.front()->report() << endl;
					readyDeque.pop_front(); // Removes process from deque
				}
				break;
			}

			case(2): { // Process interrupted

				if (!readyDeque.empty()) {
					readyDeque.front()->interrupt(); // Interrupts process
					cout << readyDeque.front()->report() << endl;
					readyDeque.push_back(readyDeque.front()); // Moves process to back of queue
					readyDeque.pop_front(); // Pops process from the front
				}
				break;
			}

			case(3): { // Process I/O or event wait

				if (!readyDeque.empty()) {
					readyDeque.front()->eventWait(); // Process I/O or event wait
					cout << readyDeque.front()->report() << endl;
					waitingDeque.push_front(readyDeque.front()); // Moves to waiting deque
					readyDeque.pop_front(); // Removes from ready deque
				}
				break;
			}

		}

		if (waiting == 1 && !waitingDeque.empty()) { //for the waiting deque decision for putting back into ready
			waitingDeque.back()->eventCompletion(); // Process I/O or event completion
			cout << waitingDeque.back()->report() << endl;
			readyDeque.push_back(waitingDeque.back()); // Moves to ready deque
			waitingDeque.pop_back(); // Removes from waiting deque
		}

	}

}