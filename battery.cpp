/*
This class serves as the AED's battery module

Private Members:

charge - the battery's capacity represented as a percentage. I.E: charge = 100 -> 100% capacity

Important Functions:

deplete(int n) - drains the battery by n%
change() - replaces the battery module with a new one
*/
#include "battery.h"

Battery::Battery(int n)
{
    this->charge = n;
}

// depletes battery by n
int Battery::deplete(int n){
    this->charge -= n;
    if(charge < 0){
        charge = 0;
    }
    return this->charge;
}
void Battery::change(){
    charge = 100;
}
int Battery::getCharge(){
    return this->charge;
}
