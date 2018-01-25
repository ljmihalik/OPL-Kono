#include "Tournament.h"
#include "Game.h"

#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

Tournament::Tournament(){

}
Tournament::~Tournament(){
    
}

/* ********************************************************************* 
Function Name: startTournament 
Purpose: display menu and start, or load game, or quit
Parameters: 
            no parameters
Return Value: no value
Local Variables: 
           Uoption --> users menu option
           new Game --> Game class object
Algorithm: 
            1) get menu option 
            2) call function according to menu option 
Assistance Received: none 
********************************************************************* */
void Tournament::startTournament(){
    Game newGame;
    int Uoption=0;
    cout<<"1. Start new game!"<<endl;
    cout<<"2. Load game!"<<endl;
    cout<<"3. Quit!"<<endl;
    cin>>Uoption;
    switch(Uoption){
        case 1:
           newGame.startGame("");
           break;
        case 2:
            //load game
            break;
        case 3:
            exit(0);
 
    }
    

}
/* ********************************************************************* 
Function Name: playAgain 
Purpose: To restart game or announce winner and quit 
Parameters: 
            no parameters
Return Value: no value
Local Variables: 
            answer to hold if they want to play again
Algorithm: 
            1) get response 
            2) restart game or 
Assistance Received: none 
********************************************************************* */
void Tournament::playAgain(){
    string answer;
    cout<<"Would you like to play again? (yes/no)"<<endl;
    cin>>answer;
/*
    switch(answer){
        //restart game
        case 'yes':
            break;
        
        case 'no':
            //announce winner--draw if scores are the same
            exit();

    }
    */

}


void Tournament::endTournament(){
    //call scoring function
    //announce winner
    exit(0);
}