#include "Tournament.h"
#include <iostream>
#include <ctime>


 using namespace std;
 int main () {
     srand(time(0));
    Tournament newTournament;
    newTournament.startTournament();
    cout<<"EVERTHYING WORKS"<<endl;
    return 0;
}