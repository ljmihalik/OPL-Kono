#include "Board.h"
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

Board::Board(){
}

Board::~Board(){
    
}

void Board::setBoard(int row, int col, string newElement){
    mBoard[row][col]=newElement;
}

/* ********************************************************************* 
Function Name: createBoard 
Purpose: to create the intial board 
Parameters: 
            no parameters
Return Value: no value returned
Local Variables: 
            row, and col to print board 
Algorithm: 
            1) get the size of board
            2) loop over to place in the B O and W's in correct spot
            3) account for the 4 pieces in the second and second to last row
Assistance Received: none 
********************************************************************* */
void Board::createBoard(int gridSize){
    mGridsize=gridSize;
    mBoard.resize(gridSize);   
    string piece;
    //make dynamic
    for(int row=0; row<gridSize; row++){
        if(row==0){
            piece="B";
        }
        else if(row==mGridsize-1){
           piece="W";
        }
        else{
            piece="O";
        }
        mBoard[row].resize(gridSize);
        for(int col=0; col<gridSize; col++){
            mBoard[row][col]=piece;
        }
    }
    mBoard[1][0]="B";
    mBoard[1][mGridsize-1]="B";
    mBoard[mGridsize-2][0]="W";
    mBoard[mGridsize-2][mGridsize-1]="W";
}

/* ********************************************************************* 
Function Name: devOption 
Purpose: To hold a winning game board for comparision 
Parameters: 
            gridSize
Return Value: no value
Local Variables: 
            pieces --> holding the B W or O
            row --> for looping rows
            col --> for looping columns
Algorithm: 
            1)  show a "winning board"
Assistance Received: none 
********************************************************************* */
void Board::devOption(int gridSize){
    mGridsize=gridSize;
    mBoard.resize(gridSize);   
    string piece;
    //make dynamic
    for(int row=0; row<gridSize; row++){
        if(row==0){
            piece="W";
        }
        else if(row==mGridsize-1){
           piece="B";
        }
        else{
            piece="O";
        }
        mBoard[row].resize(gridSize);
        for(int col=0; col<gridSize; col++){
            mBoard[row][col]=piece;
        }
    }
    mBoard[1][0]="W";
    mBoard[0][2]="O";
    mBoard[2][2]="W";
    mBoard[1][mGridsize-1]="O";
    mBoard[mGridsize-2][0]="B";
    mBoard[mGridsize-2][mGridsize-1]="B";
}



/* ********************************************************************* 
Function Name: movePiece 
Purpose: To move a piece on the board 
Parameters: 
            row and column of piece that user wants to move
            coordinate of the piece
Return Value: no value
Local Variables: 
            piece --> store the color of the piece getting moved
            newRow --> row of pieces new position
            newCol --> column of pieces new position
            Cpiece --> BB/WW if piece can capture
Algorithm: 
            1)  account of each move user can make (4 options)
            2) move the piece into the new row and column according to the option
Assistance Received: none 
********************************************************************* */
void Board::movePiece(int row, int column, string coordinate){
    string piece=mBoard[row][column];
    mBoard[row][column]="O";
    int newRow=0;
    int newCol=0;
    string Cpiece=piece;
    if(piece.length() == 1){
        Cpiece=piece+piece;
    }

    if(coordinate=="northeast"){
        newRow=row-1;
        newCol=column+1;
        mBoard[row-1][column+1]=piece;
    }
    else if (coordinate=="northwest"){
        newRow=row-1;
        newCol=column-1;
        mBoard[row-1][column-1]=piece;
    }
    else if (coordinate=="southeast"){
        newRow=row+1;
        newCol=column+1;
        mBoard[row+1][column+1]=piece;
    }
    else if(coordinate=="southwest"){
        newRow=row+1;
        newCol=column-1;
        mBoard[row+1][column-1]=piece;
    }
    if(newRow == 0 || newRow == mGridsize-1){
            //home position
            mBoard[newRow][newCol]=Cpiece;
    }
    if((newRow == 1 && newCol == 0) || (newRow == 1 && newCol == mGridsize-1)){
        mBoard[newRow][newCol]=Cpiece;
    }
    if((newRow == mGridsize-2 && newCol == 0 ) || (newRow == mGridsize-2 && newCol == mGridsize-1)){
        mBoard[newRow][newCol]=Cpiece;
    }
    
}

/* ********************************************************************* 
Function Name: validateMove 
Purpose: Error handling for the board
Parameters: 
            row --> row position of current piece
            column --> column position of current piece
            coordinate --> direction of the pieces move
            color --> what color the user picked
Return Value: false is something goes wrong otherwise true
Local Variables: 
           Upiece --> B or W 
           Cpiece --> is BB if it is a piece that can capture
           piece --> letter(s) in current positoin
           newRow --> row where piece is getting moved
           newCol --> column where piece is getting moved
Algorithm: 
            1) valid starting position
            2) out of bounds
            3) open position
            4) capture 
Assistance Received: none 
********************************************************************* */
bool Board::validateMove(int row, int column, string coordinate, string color){
    bool isValid=true;
    string Upiece;
    string Cpiece;
    

    if(color == "black"){
        Upiece="B";
        Cpiece="BB";
    }
    else{
        Upiece="W";
        Cpiece="Ww";
    }
    
    //valid starting position by color and gridsize
    if(row < 0 || row > mGridsize || column < 0 || column > mGridsize){
        cout<<"Starting position not on board!"<<endl;
        return false;
    }
    
    string piece=mBoard[row][column]; 
    
    //color
    if(piece != Upiece){
         if(piece != Cpiece){
             cout<<"Piece selected is not your color!"<<endl;
            return false;
         }
    }
   
    string newPiece;
    int newRow;
    int newCol;

    //if move is out of bounds
    if(coordinate=="northeast"){
        newRow=row-1;
        newCol=column+1;

    }
    else if (coordinate=="northwest"){
        newRow=row-1;
        newCol=column-1;
        
    }
    else if (coordinate=="southeast"){
        newRow=row+1;
        newCol=column+1;
    }
    else if(coordinate=="southwest"){
        newRow=row+1;
        newCol=column-1;
    }

    if(newRow < 0 || newRow > mGridsize || newCol < 0 || newCol > mGridsize){
        cout<<"Moving piece out of bounds!"<<endl;
        return false;
    }
    
    //if positions open
    if(coordinate=="northeast"){
        newPiece=mBoard[row-1][column+1];
    }
    else if (coordinate=="northwest"){
        newPiece=mBoard[row-1][column-1];
        
    }
    else if (coordinate=="southeast"){
        newPiece=mBoard[row+1][column+1];
    }
    else if(coordinate=="southwest"){
        newPiece=mBoard[row+1][column-1];
    }
    //can capture?
    if(newPiece == Upiece || newPiece == Cpiece){
        cout<<"You have a piece in that position!"<<endl;
        return false;
    }
    if(piece == Upiece && newPiece != "O"){
        cout<<"Not an open spot!"<<endl;
        return false;
    }
    
    return true;
}

/* ********************************************************************* 
Function Name: viewBoard 
Purpose: print the board
Parameters: 
            no parameters
Return Value: no return value
Local Variables: 
        row --> print rows
        col --> print columns
Algorithm: 
            1) nested loops to print the board 
Assistance Received: none 
********************************************************************* */
void Board::viewBoard(){
    int count=1;
    cout<<"N"<<endl;
    for(int row=0; row<mGridsize; row++){
        cout<<count;
        cout<<" ";
        count++;
        for(int col=0; col<mGridsize; col++){
            cout<<mBoard[row][col];
            cout<<"\t";
            
        }
        
        cout<<endl;
    }
    cout<<"S"<<endl;
    cout<<"W ";
    for(int horizontalNum=1; horizontalNum<=5; horizontalNum++){
        cout<<horizontalNum;
        cout<<"\t";
    }
    cout<<"E";
    cout<<"\n";
}

/* ********************************************************************* 
Function Name: checkWinner 
Purpose: checks if winner 
Parameters: 
            no parameters
Return Value: returns true if winner otherwise false
Local Variables: 
       
Algorithm: 
            1) nested loops to print the board 
Assistance Received: none 
********************************************************************* */
bool Board::checkWinner(){
    int bPieces=0;
    int wPieces=0;
    int totalB=0;
    int totalW=0;
    string piece;

    //count up all the current white and black pieces on the board in winning spots
    //check the first and last row --> then the 4 other points
    //if all available pieces are in winning position then theres a winner
    for(int row=0; row<mGridsize; row++){
        for(int col=0; col<mGridsize; col++){
            piece=mBoard[row][col];
            //looking at winning positions and counting 
            if( piece == "B" && row == mGridsize-1){
                bPieces++;
            }
            else if( piece == "BB" && row == mGridsize-1){
                bPieces++;
            }
            else if( piece == "W" && row == 0 ){
                wPieces++;
            }
            else if( piece == "WW" && row == 0){
                wPieces++;
            }

            //looking at the whole board --> counting total pieces
            if(piece =="W" || piece =="WW"){
                totalW++;
            }
            else if(piece =="B" ||piece =="BB"){
                totalB++;
            }
        }  
    }

    //looking at 2nd row and 2nd to last row's
    if(mBoard[mGridsize-2][0] == "B" || mBoard[mGridsize-2][0] == "BB"){
        bPieces++;
    }
    else if(mBoard[mGridsize-2][mGridsize-1] == "B" || mBoard[mGridsize-2][mGridsize-1] == "BB"){
        bPieces++;
    }

    if(mBoard[1][0] == "W" || mBoard[1][0] == "WW"){
        wPieces++;
    }
    else if(mBoard[1][mGridsize-1] == "W" || mBoard[1][mGridsize-1] == "WW"){
        wPieces++;
    }

    if(totalW == wPieces){ 
        return true;
    }
    else if(totalB == bPieces){
        return true;
    }

    return false;
}

/* ********************************************************************* 
Function Name: score 
Purpose: adds up score of winner. 
Parameters: 
            no parameters
Return Value: returns score
Local Variables: piece --> holds the B, BB, W, WW
                Pscore/Cscore --> holds score
                row/col --> used for looping in for loop
       
Algorithm: 
            1) home pieces 3 1 5 1 3 
            2) add up all the pieces in home positions
            3) count number of remaining peices +5 for player who captured
            5) -5 for player who quits
Assistance Received: none 
********************************************************************* */
int Board::score(string color){
    string piece;
    int Pscore=0;
    string ScorePiece;
    string ScoreCapture;
    int Scorerow=0;
    int OppPieces=0;
    int SecondScoreRow=0;


    if(color =="black"){
        ScorePiece="B";
        ScoreCapture="BB";
        Scorerow=mGridsize-1;
        SecondScoreRow=mGridsize-2;
    }
    else if(color =="white"){
        ScorePiece="W";
        ScoreCapture="WW";
        Scorerow=0;
        SecondScoreRow=1;
    }

    for(int row=0; row<mGridsize; row++){
        for(int col=0; col<mGridsize; col++){
            piece=mBoard[row][col];
            //adding scores
            if((piece == ScorePiece && row==Scorerow) || (piece == ScoreCapture && row ==Scorerow)){
                //adding 3's
                if(col==0 || col==mGridsize-1){
                    Pscore+=3;
                }
                //adding 1's
                if(col==1 || col==mGridsize-2){
                    Pscore++;
                }
                //adding 5's
                if(col==2 || col==mGridsize-3){
                    Pscore+=5;
                }
                //adding 7's
                if(mGridsize>5){
                    if(col==3 || col==mGridsize-4 ){
                        Pscore+=7;
                    }  
                    //adding 9's
                    if(mGridsize==9 && col==4){
                        Pscore+=9;
                    } 
                }
                
            }

            //count up oppentent pieces on board
            if(piece != ScorePiece && piece != ScoreCapture && piece != "O"){
                OppPieces++;
            }

        }
    }

    //calc captured score
    int PieceDiff=0;
    if(OppPieces < mGridsize+2){
        PieceDiff=mGridsize-OppPieces;
        Pscore+=PieceDiff*5;
    }
    
    //adding inner one's
    if(mBoard[SecondScoreRow][0] == ScorePiece || mBoard[SecondScoreRow][0] == ScoreCapture){
        Pscore++;
    }
    else if(mBoard[SecondScoreRow][mGridsize-1] == ScorePiece || mBoard[SecondScoreRow][mGridsize-1] == ScoreCapture){
        Pscore++;
    }

    return Pscore;
}
