#include <iostream>
#include <string>
#include <ctime>
#include <fstream>


#include "Computer.h"
#include "Human.h"
#include "Board.h"
#include "Game.h"

using namespace std;

Game::Game(){

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
void Game::startGame(string winner){
    //overwritting score here --> players variables of game?
    Computer Cplayer;
    Human Hplayer; 
    string color;
    if(winner == ""){
        srand(time(0));

        int dice1=Hplayer.rollDice();
        int dice2=Cplayer.rollDice();
        
        //equal keep askiing till higher number
        do{
            //int dice1=throwDice();
            dice1=Hplayer.rollDice();
            dice2=Cplayer.rollDice();
        }
        while(dice1 == dice2);

        //player with higher number wins toss decides color
        if(dice1 < dice2){
           //computer picks color
            color="white";
            humanTurn=false;
        }

        else if(dice1 > dice2){
            cout<<"What color do you want to be? (black/white)"<<endl;
            cin>>color;
            humanTurn=true;
        }
    }

    else{
        if(winner=="computer"){
            //have computer pick number
        }

        else{
            cout<<"What color do you want to be? (black/white)"<<endl;
            cin>>color;
        }
        
    }

    Board table;
    int gridSize=0;
    
    cout<<"Plese enter grid size 5, 7, 9"<<endl;
    cin>>gridSize;
    cout<<endl;

    table.createBoard(gridSize);
    
    table.viewBoard();

    int option=0;
    int roundNum=0;
    do{
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
                saveGame(roundNum, table, Hplayer, Cplayer);
                cout<<"Game Saved!"<<endl;
                break;

            case 2:
                cout<<"Your move! Which piece, give row and column numbers?"<<endl;
                cin>>rowPosition>>columnPosition;
               
                cout<<"Where would you like to move "<<rowPosition <<","<<columnPosition<<"?"<<endl;
                cin>>coordinate;
                
            
                isValid=table.validateMove(rowPosition, columnPosition, coordinate, color);
                
                if(isValid==true){
                    table.movePiece(rowPosition, columnPosition, coordinate);
        
                    if(table.checkWinner()== 1){
                        //winner --> check score and declare winner
                        //NEED to make this dynamic!!
                        // Hplayer.color --> dynamic
                        int computerScore=table.score("white");
                        int HumanScore=table.score("black");
                        if(computerScore < HumanScore){
                            //human wins!
                            cout<<"You win!"<<endl;
                        }
                        else if(computerScore > HumanScore){
                            //computer wins!
                            cout<<"Computer win!"<<endl;
                        }
                        //what to do on Tie??
                        else{
                            cout<<"The games a Draw!"<<endl;
                        }
                    }
                    table.viewBoard();
                }
                
        
                //have computers move

                break;

            case 3:
                //call computer
                break;

            case 4:
                table.devOption(gridSize);

                if(table.checkWinner()== 1){
                    //winner -- get score
                }
                table.viewBoard();

            case 5:
                //call end game;
                break;
        }

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
       
Algorithm: 
            1) get file name
            2) open file
            3) getlines of file
            4) assign variables to correct values
            5)start game from those variables
Assistance Received: none 
********************************************************************* */
void Game::loadGame(Board& table){
    ifstream file;
    string Fname;
    string line;
    int roundNum=0;
    int Findex;
    string contents;
    int Cscore=0;
    int Hscore=0;
    string Ccolor;
    string Hcolor;
    string NextPlayer;

    cout<<"Please enter file name."<<endl;
    cin>>Fname;
    file.open(Fname);
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
                    Cscore=atoi(line.c_str());
                }

                getline(file, line, ':');
                if(line=="   Color"){ 
                    getline(file, line); 
                    Ccolor=line;
                    getline(file, line);
                }
            }

            if(line =="Human"){
                getline(file, line);
                getline(file, line, ':');
                if(line=="   Score"){
                    
                    getline(file, line); 
                    Hscore=atoi(line.c_str());
                    
                }

                getline(file, line, ':');
                if(line=="   Color"){ 
                    getline(file, line); 
                    Hcolor=line;
                    getline(file, line);
                    //getline(file, line);
                }
            }

            if(line == "Board"){
                
                getline(file, line);
                getline(file, line);

                //loop over all lines in board
                //issue in setBoard()--> char and string
                int row=0;
                int col=0;
                
                cout<<"HERE"<<line<<endl;
                for(int index=0; index<=line.length(); index++){
                    if(line[index] != ' '){
                        table.setBoard(row, col, line[index]);
                        col++;
                    }
                }
                getline(file, line);
                


            }

            if(line=="Next Player"){
                getline(file, line);
                NextPlayer=line;
            }
    
        }
    }
    

}
