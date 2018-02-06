#include "Board.h"
#include "Boardview.h"
#include <iostream>
using namespace std;

Boardview::Boardview(){

}

Boardview::~Boardview(){

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
void Boardview::viewBoard(Board& table){
    int count=1;
     vector<vector<string> > lBoard=table.getBoard();
    cout<<"N"<<endl;
    for(int row=0; row<table.mGridsize; row++){
        cout<<count;
        cout<<" ";
        count++;
        for(int col=0; col<table.mGridsize; col++){
            cout<<lBoard[row][col];
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
