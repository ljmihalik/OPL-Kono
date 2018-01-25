#include <iostream>
#include <string>
#include <ctime>

#include "Game.h"
#include "Computer.h"
#include "Human.h"
#include "Board.h"

using namespace std;

Game::Game(){

}
Game::~Game(){

}
void Game::startGame(string winner){
    
    string color;
    if(winner == ""){
        srand(time(0));

        Computer Cplayer;
        Human Hplayer; 
        
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
            cout<<"What color do you want to be? (black/white)"<<endl;
            cin>>color;
        }

        else if(dice1 > dice2){
            cout<<"What color do you want to be? (black/white)"<<endl;
            cin>>color;
        }
    }

    else{
        if(winner=="computer"){
            //habe computer pick number
        }

        else{
            cout<<"What color do you want to be? (black/white)"<<endl;
            cin>>color;
        }
        
    }

    Board table;
    Game toss;
    int gridSize=0;
    
    cout<<"Plese enter grid size 5, 7, 9"<<endl;
    cin>>gridSize;
    cout<<endl;

    table.createBoard(gridSize);
    
    table.viewBoard();

    int option=0;

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
                break;

            case 2:
                cout<<"Your move! Which piece, give row and column numbers?"<<endl;
                cin>>rowPosition>>columnPosition;
               
                
                cout<<"Where would you like to move "<<rowPosition <<","<<columnPosition<<"?"<<endl;
                cin>>coordinate;
                
            
                isValid=table.validateMove(rowPosition, columnPosition, coordinate, color);
                
                if(isValid==true){
                    table.movePiece(rowPosition, columnPosition, coordinate);
                    table.viewBoard();
                }
                
        
                //have computers move

                break;

            case 3:
                //call computer
                break;

            case 4:
                table.devOption(gridSize);
                table.checkWinner();
                table.viewBoard();

            case 5:
                //call end game;
                break;
        }
        //table.checkWinner();
    }
    while(true);
}