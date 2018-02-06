

#include "Board.h"
#include "Computer.h"
#include "Human.h"
#include "Game.h"
#include "Tournament.h"

#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

Tournament::Tournament(){
    Rounds=0;

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
           uOption --> users menu option
           new Game --> Game class object
           hPlayer --> Human class object
           cPlayer --> Comupter class object
           table --> Board class object
           result --> bool - true if someone wine false is player quits
Algorithm: 
            1) get menu option 
            2) call function according to menu option 
            3) account for ending game/ announcing winner
Assistance Received: none 
********************************************************************* */
void Tournament::startTournament(){
    //class objects
    Computer cPlayer;
    Human hPlayer; 
    Game newGame;
    Board table;

    bool result;
    int uOption=0;

    cout<<"1. Start new game!"<<endl;
    cout<<"2. Load game!"<<endl;
    cout<<"3. Quit!"<<endl;
    cin>>uOption;
    
    string answer;
    switch(uOption){
        
        //start game
        case 1:

            do{
               result=newGame.startGame(newGame.Winner, hPlayer, cPlayer); 
               Rounds++;
               
               //false is returned when player quits game
               if(result==false){
                   hPlayer.deductScore();
               }
               
                //always check if player want to play again whether they win or quit
                cout<<"Would you like to play again? (yes/no)"<<endl;
                cin>>answer;

                if(answer=="yes"){
                    //start game
                    result=true;
                }

                else{
                    //announce winner and quit
                    endTournament(hPlayer.getScore(), cPlayer.getScore());
                }
            }
           while(result==true);

           break;

        //load game
        case 2:
            //load game
           newGame.loadGame(hPlayer, cPlayer);
            break;

        //exit
        case 3:
            exit(0);
 
    }
    

}

/* ********************************************************************* 
Function Name: endTournament 
Purpose: announce winner, print score and quit
Parameters: 
            hScore --> human score
            cScore --> computer score
Return Value: no value
Local Variables: 
          no local variable
Algorithm: 
            1) check who won
            2) check for draw
            3) exit/quit
Assistance Received: none 
********************************************************************* */
void Tournament::endTournament(int hScore, int cScore){
    //announce winner
    if(cScore < hScore){
        //human wins!
        cout<<"You win!"<<endl;
        cout<<"Human Score: "<<hScore<<endl;
        cout<<"Computer Score: "<<cScore<<endl;
        cout<<"Round Numbers: "<<Rounds<<endl;
    }

    else if(cScore > hScore){
        //computer wins!
        cout<<"Computer win!"<<endl;
        cout<<"Human Score: "<<hScore<<endl;
        cout<<"Computer Score: "<<cScore<<endl;
        cout<<"Round Numbers: "<<Rounds<<endl;
    }

    //draw
    else{
        cout<<"The games a Draw!"<<endl;

    }

    exit(0);
}

