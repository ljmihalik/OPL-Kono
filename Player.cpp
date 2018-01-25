#include "Player.h"
#include <string>

Player::Player(){

}

Player::~Player(){

}

/* ********************************************************************* 
Function Name: rollDice 
Purpose: Generate random number and get sum 
Parameters: 
            no parameters
Return Value: integer --> sum of 2 random numbers
Local Variables: 
            die1 --> 1st random number
            die2 --> 2nd random number
            total --> sum of die1 die 2
Algorithm: 
            1) generate random number
            2) add sums 
Assistance Received: none 
********************************************************************* */
int Player::rollDice(){
    //generate random number
        die1= rand() % 6 + 1;
        die2= rand() % 6 + 1;
        total=die1+die2;
        return total;
}