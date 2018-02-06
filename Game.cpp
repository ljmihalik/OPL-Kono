#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include<algorithm>

#include "Boardview.h"
#include "Computer.h"
#include "Piece.h"
#include "Tournament.h"
#include "Human.h"
#include "Board.h"
#include "Game.h"

using namespace std;

Game::Game(){
    Winner="";
    

}
Game::~Game(){

}

/* ********************************************************************* 
Function Name: startGame 
Purpose: initiates game 
Parameters: 
            winner --> takes winner if player is starting again.
Return Value: void function --> no return value
Local Variables: 
            color --> color of pieces
            dice1/ dice2 --> random number from rolldice function
            gridSize --> size indicated by user
            roundNum --> number of round game is on
            option --> menu option choosen by user
            row/colPosition --> the position of piece they want to move
            coordinate --> where user wants to move piece
            isValid --> error checking
       
Algorithm: 
            1) check if winner
            2) roll dice --> find winner
            3) get all user info
            4) error handling on move piece
             
Assistance Received: none 
********************************************************************* */
bool Game::startGame(string winner, Human& hPlayer, Computer& cplayer){
    string color;
    int gridSize=0;
    Boardview view;
    
    cout<<"Plese enter grid size 5, 7, 9"<<endl;
    cin>>gridSize;
    cout<<endl;

    if(winner == ""){
        srand(time(0));

        int dice1=hPlayer.rollDice();
        int dice2=cplayer.rollDice();
        
        //equal keep askiing till higher number
        do{
            //int dice1=throwDice();
            dice1=hPlayer.rollDice();
            dice2=cplayer.rollDice();
        }
        while(dice1 == dice2);

        //player with higher number wins toss decides color
        if(dice1 < dice2){
           //computer picks color
            cplayer.color="white";
            if(cplayer.color=="white"){
                hPlayer.color="black";
            }
            else{
                hPlayer.color="white";
            }

            cout<<"Computer won the roll it picked: "<<cplayer.color<<" as its color!"<<endl;
            humanTurn=false;
        }

        else if(dice1 > dice2){
            cout<<"You won roll! ";
            cout<<"What color do you want to be? (black/white)"<<endl;
            cin>>color;
            hPlayer.color=color;

            if(hPlayer.color=="black"){
                cplayer.color="white";
            }
            else{
                cplayer.color="black";
            }

            humanTurn=true;
        }
    }

    else{
        if(winner=="computer"){
            //have computer pick number
            cplayer.color="white";
            if(cplayer.color=="white"){
                hPlayer.color="black";
            }
            else{
                hPlayer.color="white";
            }
            humanTurn=false;
        }

        else{
            cout<<"What color do you want to be? (black/white)"<<endl;
            cin>>color;
            hPlayer.color=color;
            humanTurn=true;

            if(hPlayer.color=="black"){
                cplayer.color="white";
            }
            else{
                cplayer.color="black";
            }
        }
        
    }

    
    table.createBoard(gridSize);
    
    view.viewBoard(table);

    int option=0;
    int roundNum=0;
    Piece CNextMove(0,0);
    Piece PNextMove(0,0);

    Tournament tourn;

    int computerScore=0;
    int humanScore=0;

    do{
        //have computers move
        if(humanTurn==false){
            CNextMove=cplayer.CMovePiece(table);
            table.movePiece(CNextMove.Row, CNextMove.Col, CNextMove.Coordinate, cplayer.color);
            cout<<"The computer moved the piece at ("<<(CNextMove.Row+1)<<","<<(CNextMove.Col+1)<<") "<<CNextMove.Coordinate<<endl;
            if(table.checkWinner()== 1){
                            
                //winner --> check score and declare winner
                //NEED to make this dynamic!!
                // hPlayer.color --> dynamic
                computerScore=table.score(cplayer.color);
                humanScore=table.score(hPlayer.color);
                cplayer.addScore(computerScore);
                hPlayer.addScore(humanScore);

                if(computerScore < humanScore){
                    //human wins!
                    cout<<"You win!"<<endl;
                    cout<<"Human Score: "<<humanScore<<endl;
                    cout<<"Computer Score: "<<computerScore<<endl;

                    Winner="human";
                }
                else if(computerScore > humanScore){
                    //computer wins!
                    cout<<"Computer win!"<<endl;
                    cout<<"Human Score: "<<humanScore<<endl;
                    cout<<"Computer Score: "<<computerScore<<endl;

                    Winner="computer";

                }
                //what to do on Tie??
                else{
                    cout<<"The games a Draw!"<<endl;
                    Winner="";
                }
                view.viewBoard(table);

                return true;
            }
            view.viewBoard(table);
        }

                
        else{

            cout<<"1. Save game!"<<endl;
            cout<<"2. Make a move!"<<endl;
            cout<<"3. Ask for help!"<<endl;
            cout<<"4. Developer Option"<<endl;
            cout<<"5. Quit!"<<endl;
            cin>>option;

            string coordinate;
            int rowPosition=0;
            int columnPosition=0;
            bool isValid=true;
        
            
            switch(option){
                case 1:
                    //call serialization
                    saveGame(roundNum, table, hPlayer, cplayer);
                    cout<<"Game Saved!"<<endl;
                    exit(0);
                    break;

                case 2:

                    cout<<"Your move! Which piece, give row and column numbers?"<<endl;
                    cin>>rowPosition>>columnPosition;
                    rowPosition-=1;
                    columnPosition-=1;
                
                    cout<<"Where would you like to move "<<(rowPosition+1) <<","<<(columnPosition+1)<<"?"<<endl;
                    cin>>coordinate;
                    
                    isValid=table.validateMove(rowPosition, columnPosition, coordinate, hPlayer.color);
                    
                    if(isValid==true){
                        table.movePiece(rowPosition, columnPosition, coordinate, hPlayer.color);
            
                        if(table.checkWinner()== 1){
                            
                            //winner --> check score and declare winner
                            //NEED to make this dynamic!!
                            // hPlayer.color --> dynamic
                            computerScore=table.score(cplayer.color);
                            humanScore=table.score(hPlayer.color);
                            
                            if(computerScore < humanScore){
                                //human wins!
                                cout<<"You win!"<<endl;
                                cout<<"Human Score: "<<humanScore<<endl;
                                cout<<"Computer Score: "<<computerScore<<endl;

                                Winner="human";
                            }
                            else if(computerScore > humanScore){
                                //computer wins!
                                cout<<"Computer win!"<<endl;
                                cout<<"Human Score: "<<humanScore<<endl;
                                cout<<"Computer Score: "<<computerScore<<endl;
                                
                                Winner="computer";
                            }
                            //what to do on Tie??
                            else{
                                cout<<"The games a Draw!"<<endl;
                                Winner="";
                            }
                            
                            return true;
                        }
                        view.viewBoard(table);
                    }
                
                    break;

                case 3:
             
                    PNextMove=hPlayer.Help(table);
                    //cout<<PNextMove<<endl;
                
                    cout<<"The computer suggests: ("<<(PNextMove.Row+1)<<", "<<(PNextMove.Col+1)<<") "<<(PNextMove.Coordinate)<<" as your next move"<<endl;
                    cout<<endl;
                    humanTurn=true;
                    break;

                case 4:
                    table.devOption(gridSize);
                
                    view.viewBoard(table);
                    break;

                case 5:
                    //call end game;
                    cout<<"Quitting game"<<endl;
                    return false;
            
            }
        }

        //changing turns for computer/human
        if(humanTurn==true){
            humanTurn=false;
        }
        
        else if(humanTurn==false){
            humanTurn=true;
        }

        //should track tournament
        roundNum++;
    }
    while(true);
}

/* ********************************************************************* 
Function Name: saveGame 
Purpose: save current instance of the game 
Parameters: 
            roundNum --> the round number the game is on
            color --> color of player

Return Value: void function
Local Variables: 
       file --> file to save game too
       row --> loop through rows of board
       col --> loop throguh columns of board
       lBoard --> to hold board
Algorithm: 
            1) open file
            2) write game info into file
            3) close file 
Assistance Received: none 
********************************************************************* */
void Game::saveGame(int roundNum, Board& table, Human& person, Computer& AI){
    ofstream file;
    vector<vector<string> > lBoard=table.getBoard();

    file.open("SavedGame.txt");
    
    file<<"Round: "<<roundNum<<endl;
    file<<'\n';

    file<<"Computer:"<<endl;
    file<<'\t'<<"Score: "<< AI.getScore()<<endl;
    file<<'\t'<<"Color: "<<AI.color<<endl;
    file<<'\n';

    file<<"Human:"<<endl;
    file<<'\t'<<"Score: "<<person.getScore()<<endl;
    file<<'\t'<<"Color: "<<person.color<<endl;
    file<<'\n';

    file<<"Board:"<<endl;
     for(int row=0; row<table.mGridsize; row++){
        for(int col=0; col<table.mGridsize; col++){
            file<<lBoard[row][col];
            file<<"   ";
            
        }
        file<<endl;
    }
    file<<'\n';
    if(humanTurn==false){
        file<<"Next Player: Human"<<endl;   
    }
    else if(humanTurn==true){
        file<<"Next Player: Computer"<<endl;   
    }
}

/* ********************************************************************* 
Function Name: loadGame 
Purpose: loads a file of an old game 
Parameters: 
            no parameters
Return Value: void function
Local Variables: 
            file --> ifstream to hold the file
            Fname --> string to hold file name
            line --> string to hold the contents of the line being read
            roundNum --> int to hold round number
            contents --> size_t to hold index where places are
            cScore --> int to hold computer score
            hScore --> int to hold human score
            nextPlayer --> string to hold next player
       
Algorithm: 
            1) get file name
            2) open file
            3) getlines of file
            4) assign variables to correct values
            5)start game from those variables

Assistance Received: had to look up the remove whitespace and to_lower function online
    remove_if found: http://www.cplusplus.com/reference/algorithm/remove_if/
    transform http://www.cplusplus.com/reference/algorithm/transform/
********************************************************************* */
void Game::loadGame(Human& hPlayer, Computer& cplayer){
    ifstream file;
    string Fname;
    string line;
    int roundNum=0;
    size_t contents;
    int cScore=0;
    int hScore=0;
    string nextPlayer;

    //get file name and open file
    cout<<"Please enter file name."<<endl;
    cin>>Fname;
    file.open(Fname);

    //error handling for if file is no found
    if(!file){
        cout<<"No file opened!"<<endl;
    }
    else{
        cout<<"File opened"<<endl;

        while(getline(file, line, ':')){
            cout<<line<<endl;
          
            if(line == "Round"){
            getline(file, line);
            roundNum=atoi(line.c_str());
            getline(file, line);
            }
            
            if(line=="Computer"){
                getline(file, line);
                //getline(file, line);
                getline(file, line, ':');

                if(line=="   Score"){
                    getline(file, line); 
                    cScore=atoi(line.c_str());
                    cplayer.addScore(cScore);
                }

                getline(file, line, ':');

                if(line=="   Color"){ 
                    getline(file, line); 
                    
                    //deleting leading spaces
                    contents=line.find_first_not_of(' ');
                    line.erase(0,contents);
                    transform(line.begin(), line.end(), line.begin(), ::tolower);
                    cplayer.color=line;
                    
                    cout<<cplayer.color<<endl;
                    getline(file, line);
                }
            }

            if(line =="Human"){
                getline(file, line);
                getline(file, line, ':');
                if(line=="   Score"){
                    
                    getline(file, line); 
                    hScore=atoi(line.c_str());
                    
                    hPlayer.addScore(hScore);
                    
                }

                getline(file, line, ':');
                if(line=="   Color"){ 
                    getline(file, line); 
                    
                    contents=line.find_first_not_of(' ');
                    line.erase(0,contents);
                    transform(line.begin(), line.end(), line.begin(), ::tolower);
                    hPlayer.color=line;

                    getline(file, line);
                }
            }

            if(line == "Board"){
                
                getline(file, line);
                getline(file, line);

                //loop over all lines in board
                //should these go up?
                int row=0;
                int col=0;
                char lineIndex;
                int size=0;
                while(line.length() !=0){
                    for(int index=0; index<line.length(); index++){
                        
                    
                        if(line[index] != ' ' && line[index] != '\n'){
                           cout<<row<<" "<<col<<" "<<index<<endl;
                            line.erase(remove(line.begin(), line.end(), ' '), line.end());
                            size=line.length();
                            cout<<"heer "<<line<<endl;
                            lineIndex=line[index];
                            
                            cout<<lineIndex<<endl;
                            table.setBoard(row, col, lineIndex, size);
                            cout<<"in if statement"<<endl;
                            col++;
                        }
                    
                    }
                    row++;
                    getline(file, line);
                }
                
            }

            if(line=="Next Player"){
                getline(file, line);
                contents=line.find_first_not_of(' ');
                line.erase(0,contents);
                transform(line.begin(), line.end(), line.begin(), ::tolower);
                nextPlayer=line;
            }
        }
    }
}

