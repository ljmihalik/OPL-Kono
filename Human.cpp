#include "Board.h"
#include "Human.h"
#include "Player.h"
#include "Piece.h"
#include <string>

#include <iostream>
using namespace std;

Human::Human(){

}
Human::~Human(){
    
}

Piece Human::Help(Board& table){
    vector<vector<string> > lBoard=table.getBoard();
    vector<Piece> boardPieces;
    string scorePiece;
    string scoreCapture;
    int scoreRow=0;
    int secondScoreRow=0;
    //getting the 
    int lowRow=0;
    int low=0;

    
    string oppPiece;
    string capOppPiece;
    string forward;
    string backward;
    
    int homeRow=0;
    int nextHomeRow=0;

    //cout<<table.mGridsize<<endl;
    //want to kno the color because you need to know which row is considered scoring row for each color
    if(color =="black"){
        scorePiece="B";
        scoreCapture="BB";

        oppPiece="W";
        capOppPiece="WW";

        scoreRow=table.mGridsize-1;
        secondScoreRow=table.mGridsize-2;
        lowRow=1;
        
        forward="south";
        backward="north";

        homeRow=1;
        nextHomeRow=2;

    }
    else if(color =="white"){
        scorePiece="W";
        scoreCapture="WW";

        oppPiece="B";
        capOppPiece="BB";

        scoreRow=0;
        secondScoreRow=1;
        lowRow=table.mGridsize-2;

        forward= "north";
        backward="south";

        homeRow=table.mGridsize-1;
        nextHomeRow=table.mGridsize-2;
    }
    string lPiece;
    string nePiece;
    string nwPiece;
    string sePiece;
    string swPiece;
    string move;
    vector<string> movePiece;
    

    for(int row=0; row<table.mGridsize; row++){ 
        for(int col=0; col<table.mGridsize; col++){
            
            movePiece.erase(movePiece.begin(), movePiece.end());
            lPiece=lBoard[row][col];
            
            if(lPiece == scorePiece || lPiece == scoreCapture){
                Piece BoardPiece(row, col);
               
                //southeast
                if(row+1 < table.mGridsize && col+1 < table.mGridsize){
                    sePiece=lBoard[row+1][col+1];

                    //valid moves
                    if(sePiece == "O" || (lPiece ==scoreCapture && sePiece == oppPiece) || (lPiece ==scoreCapture && sePiece== capOppPiece)){
                        movePiece.push_back("southeast");

                    }
                }

                if(row+1 < table.mGridsize && col-1 >= 0){
                    swPiece=lBoard[row+1][col-1];
                    //valid moves
                    if(swPiece == "O" || (lPiece ==scoreCapture && swPiece == oppPiece) || (lPiece ==scoreCapture && swPiece== capOppPiece)){
                        movePiece.push_back("southwest");
                    }
                }

               if(row-1 >= 0 && col-1 >= 0){
                    nwPiece=lBoard[row-1][col-1];
                    //valid moves
                    if(nwPiece == "O" || (lPiece ==scoreCapture && nwPiece == oppPiece) || (lPiece ==scoreCapture && nwPiece== capOppPiece)){
                        movePiece.push_back("northwest");
                    }
                }

                if(row-1 >= 0 && col+1 < table.mGridsize){
                    nePiece=lBoard[row-1][col+1];
                    //valid moves
                    if(nePiece == "O" || (lPiece ==scoreCapture && nePiece == oppPiece) || (lPiece ==scoreCapture && nePiece== capOppPiece)){
                        movePiece.push_back("northeast");
                    }
                }
              
                //X -move forward first, 
                //unless a capture piece 
                    //prioritize backward moves
                //-if piece can capture another
                //-move backwards

                //piece class to store final move
                // 1 piece --> 4 possible moves
                //evaulte each piece on board
                //select best move of best move
                //have attribute bool piece.homepos --> need to know score
                //if scoring position --> true/false ---> record values (point value)

                //value used for checking direction
                string lCoordinate;
                
                
                //value thats been selected
                BoardPiece.Coordinate="";
                
                for(int index=0; index < movePiece.size(); index++){
                    lCoordinate=movePiece[index];
                    
                    //BB WW moving backard is 2nd priority 
                    //capture piece --> only move if capture piece in home position and can capture another piece
                        //else move it back

                    if(lPiece == scorePiece){
                        //forward is more important

                        //checking if home position
                        if( row == homeRow || (row==nextHomeRow && col==0) || (row==nextHomeRow && col==table.mGridsize-1)){
                            BoardPiece.homePosition=true;
                               //adding 3's
                            if(col==0 || col==table.mGridsize-1){
                                BoardPiece.homePositionValue=3;
                            }
                            //adding 1's
                            if(col==1 || col==table.mGridsize-2){
                                BoardPiece.homePositionValue=1;
                            }
                            //adding 5's
                            if(col==2 || col==table.mGridsize-3){
                                BoardPiece.homePositionValue=5;
                            }
                            //adding 7's
                            if(table.mGridsize>5){
                                if(col==3 || col==table.mGridsize-4 ){
                                    BoardPiece.homePositionValue=7;
                                }  
                                //adding 9's
                                if(table.mGridsize==9 && col==4){
                                    BoardPiece.homePositionValue=9;
                                } 
                            }

                        }
                        int newRow=0;
                        int newCol=0;
                        if(lCoordinate.substr(0, 5) == forward){
                            if(lCoordinate == "northeast"){
                                newRow=row-1;
                                newCol=col+1;
                            }
                            else if(lCoordinate == "northwest"){
                                newRow=row-1;
                                newCol=col-1;
                            }
                            else if(lCoordinate == "southeast"){
                                newRow=row+1;
                                newCol=col+1;
                            }
                            else if(lCoordinate == "southwest"){
                                newRow=row+1;
                                newCol=col-1;
                            }
                            int tempScore=0;
                            
                        
    
                            if(newRow == scoreRow || (newRow==secondScoreRow && newCol==0) || (newRow==secondScoreRow && newCol==table.mGridsize-1)){
                                
                                BoardPiece.scorePosition=true;
                                
                                //adding 3's
                                if(col==0 || col==table.mGridsize-1){
                                    tempScore=3;
                                }
                                //adding 1's
                                if(col==1 || col==table.mGridsize-2){
                                    tempScore=1;
                                }
                                //adding 5's
                                if(col==2 || col==table.mGridsize-3){
                                    tempScore=5;
                                }
                                //adding 7's
                                if(table.mGridsize>5){
                                    if(col==3 || col==table.mGridsize-4 ){
                                        tempScore=7;
                                    }  
                                    //adding 9's
                                    if(table.mGridsize==9 && col==4){
                                        tempScore=9;
                                    } 
                                }

                                if(tempScore > BoardPiece.ScoreValues){
                                    BoardPiece.ScoreValues=tempScore;
                                    BoardPiece.Coordinate=lCoordinate;
                                    BoardPiece.moveDirection="forward";
                                    BoardPiece.Capture=false;
                                }

                            }
                            
                            if(BoardPiece.scorePosition==false){
                                    //check if its moving to a scoring pos --> dont pick randomly
                                //prioritize higher value

                                //checking current move direction
                                if(BoardPiece.Coordinate.substr(0,5)==forward){
                                    int tieBreak=0;
                                    tieBreak= rand() % 2 + 1;


                                    if(tieBreak == 1){
                                        BoardPiece.Coordinate=lCoordinate;
                                        BoardPiece.moveDirection="forward";
                                        BoardPiece.Capture=false;

                                    }

                                }

                                else{
                                    BoardPiece.Coordinate=lCoordinate;
                                    BoardPiece.moveDirection="forward";
                                    BoardPiece.Capture=false;
                                }
                            }
                        }   

                    
                        else{
                            //checking current move direction
                            if(BoardPiece.Coordinate.substr(0,5)==backward){
                                int tieBreak=0;
                                tieBreak= rand() % 2 + 1;
                                
                                if(tieBreak == 1){
                                    BoardPiece.Coordinate=lCoordinate;
                                    BoardPiece.moveDirection="backward";
                                    BoardPiece.Capture=false;
                                }
                            }
                            else{
                                BoardPiece.Coordinate=lCoordinate;
                                BoardPiece.moveDirection="backward";
                                BoardPiece.Capture=false;
                            }
                        }   
                    }
                }
                
                if(movePiece.size()>0){
                    boardPieces.push_back(BoardPiece);
                }
                 
            }

        }

    }

    //pick best of best move --> move 1 piece
    //move to highest score position value --> need to know if its a score position and highest value
    Piece finalPiece(0,0);
   
    for(int value=0; value<boardPieces.size(); value++){
        if(value==0){
            finalPiece=boardPieces[value];
        }

        else{
            
            if(boardPieces[value].scorePosition==true){
                
                if(finalPiece.scorePosition ==true){
                    if(boardPieces[value].ScoreValues > finalPiece.ScoreValues){
                        finalPiece=boardPieces[value];
                    }
                }
                else{
                    finalPiece=boardPieces[value];
                }
            }
            else if(boardPieces[value].scorePosition==false){
              
                if(finalPiece.scorePosition ==false){
                    //account for capture piece     
                    if(boardPieces[value].moveDirection =="forward"){
                        if(finalPiece.moveDirection == "forward"){
                            if(boardPieces[value].homePosition==true){
                                if(finalPiece.homePosition==true){
                                    if(boardPieces[value].homePositionValue < finalPiece.homePositionValue){
                                        cout<<"Computer wanted to pick lowest home position value."<<endl;
                                        finalPiece=boardPieces[value];
                                    }
                                }

                                //
                                else{
                                    if(boardPieces[value].homePositionValue ==1){
                                        int num=0;
                                        num=rand()% 2+1;
                                        
                                        if(num==1){
                                            finalPiece=boardPieces[value];
                                            
                                        }
                                        
                                    }
                                    else if(boardPieces[value].homePositionValue >1){
                                        int num=0;
                                        num=rand()% 4+1;
                                        if(num==1){
                                            finalPiece=boardPieces[value];
                                        }
                                    }
                                }
                            }

                            //in relation to BoardPiece[value].homeposition==false
                            else{
                                if(finalPiece.homePosition==true){
                                    if(finalPiece.homePositionValue ==1){
                                        int num=0;
                                        num=rand()% 2+1;
                                        if(num==1){
                                            finalPiece=boardPieces[value];
                                        }
                                        
                                    }
                                    else if(finalPiece.homePositionValue > 1){
                                        int num=0;
                                        num=rand()% 4+1;
                                        if(num==1){
                                            finalPiece=boardPieces[value];
                                        }

                                    }
                                }
                                else{
                                    int num=0;
                                    num=rand()% 2+1;
                                    if(num==1){
                                        finalPiece=boardPieces[value];
                                    }
                                }
                            }

                        }

                        //final piece != forward
                        else{
                            finalPiece=boardPieces[value];
                        }
                    }
                    else{
                        if(finalPiece.moveDirection=="backward"){
                            int num=0;
                            num=rand()% 2+1;
                            if(num==1){
                                finalPiece=boardPieces[value];
                            }
                        }
                    }
                }
            }
        }
    }
    return finalPiece;
}
