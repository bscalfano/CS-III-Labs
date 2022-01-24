// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::cin; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	 makeMove(i);
	 if (i==playersCount_-1) 
	    ++movesCount_; 
      }
      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	 const int chance = (rand() % maxMoves_) / experience_[player];
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 2; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 5; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};

// Dice - another game implementing
// primitive operations
class Dice: public Game {
public:
   void initializeGame(){
      srand(time(nullptr)); // Rand seed
      playersCount_ = numPlayers_; // initalize players
      movesCount_ = 0;
      playerPass = false;
      cpuPass = false;
      playerHighScore_ = 0;
      cpuHighScore_ = 0;
      for(int i = 0; i < numRolls_; ++i){
         playerDice[i] = 0;
         cpuDice[i] = 0;
      }
      cout << "Dice game started" << endl;
   }

   void makeMove(int player){
      if (movesCount_ >= 3 || (playerPass && cpuPass)){
         playerWon_ = cpuHighScore_ >= playerHighScore_ ? 0 : 1;
      }

      if(movesCount_ > 0 && player == 0){
         cout << "Roll again? [y/n] ";
         char rollChar;
         cin >> rollChar;
         playerPass = (rollChar == 'y') ? false : true;
      }

      if(player == 0){    // CPU's turn
         cpuCurrentScore_ = 0;
         cpuPass = (rand() % 2 == 0) ? true : false;
         if(!cpuPass || cpuDice[0] == 0){  // Randomly chooses to pass or not, unless cpu has not rolled yet
            for(int i = 0; i < numRolls_; ++i){
               cpuDice[i] = ((rand() % 6) + 1);  // Set all dice
               cpuCurrentScore_ += cpuDice[i];  // Add die to current score
            }
            if(cpuCurrentScore_ > cpuHighScore_) cpuHighScore_ = cpuCurrentScore_; // Update high score
            
            cout << "Computer rolled: ";
            for(int i = 0; i < numRolls_; ++i){
               cout << cpuDice[i] << " ";
            }
            cout << "= " << cpuCurrentScore_ << ", computer's highest score = " << cpuHighScore_ << endl;
         }
         else{   // CPU pass
            cout << "Computer passed, computer's highest score = " << cpuHighScore_ << endl;
         }
      }
      else{  // Player's turn
         if(!playerPass){
            playerCurrentScore_ = 0;
            for(int i = 0; i < numRolls_; ++i){
               playerDice[i] = ((rand() % 6) + 1);  // Set all dice
               playerCurrentScore_ += playerDice[i];  // Add die to current score
            }
            if(playerCurrentScore_ > playerHighScore_) playerHighScore_ = playerCurrentScore_; // Update high score
            
            cout << "You rolled: ";
            for(int i = 0; i < numRolls_; ++i){
               cout << playerDice[i] << " ";
            }
            cout << "= " << playerCurrentScore_ << ", your highest score = " << playerHighScore_ << endl;
         }
         else{
            cout << "You passed, your highest score = " << playerHighScore_ << endl;
         }
      }
   }

   void printWinner(){
      if(playerWon_ == 1) cout << "You win!" << endl;
      else cout << "You lose!" << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int numRolls_ = 5;
   int playerDice[numRolls_];
   int cpuDice[numRolls_];
   int playerCurrentScore_;
   int cpuCurrentScore_;
   int playerHighScore_;
   int cpuHighScore_;
   bool playerPass;
   bool cpuPass;
};

int main() {
   srand(time(nullptr));

   Game* gp = nullptr;

   /* 
   // play chess 10 times
   for (int i = 0; i < 10; ++i){ 
      gp = new Chess;
      gp->playGame(); 
      delete gp;
   }
      

   // play monopoly 8 times
   for (int i = 0; i < 8; ++i){
      gp = new Monopoly;
      gp->playGame(); 
      delete gp;
   }
   */
   gp = new Dice;
   gp->playGame();
   delete gp;
}