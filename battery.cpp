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

int Battery::getCharge(){
    return this->charge;
}
