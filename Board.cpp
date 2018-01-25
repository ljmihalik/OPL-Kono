#include "Board.h"
#include <iomanip>
#include <iostream>
using namespace std;

Board::Board(){
}

Board::~Board(){
    
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
            1) build board
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
            1)  
            2) 
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
    mBoard[1][0]="O";
    mBoard[0][2]="O";
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
            1)  
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
        
        //counting the pieces in winning position
        if(row == 0){
            wPieces++;
            cout<<"HEREE"<<wPieces<<endl;
            
        }
        else if(row == mGridsize-1){
            bPieces++;
            //cout<<"HEREE"<<bPieces<<endl;
        }
        for(int col=0; col<mGridsize; col++){
            piece=mBoard[row][col];
            //counting total pieces on board --> dont care if its in winning positions or not
            if( piece == "B"){
                totalB++;
               // cout<<totalB<<endl;
            }
            else if( piece == "W"){
                totalW++;
            }
            if((row == 1 && col == 0) || (row == mGridsize-1 && col == 2) ){
                    wPieces++;
            }
            else if((row == mGridsize-2 && col == 0) || (row == mGridsize-2 && col == mGridsize-1) ){
                    bPieces++;
            }

            //counting current pieces
        }
        
        
        
    }
    return true;
}
