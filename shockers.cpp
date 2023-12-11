/*
This class serves as the AED's shocker pads

Private Members:

chargeUp - charges up the bad based on signal from master control
setPower - different power levels for adult and child pads
*/
#include "shockers.h"
#include <QDebug>

Shockers::Shockers()
{
    charged = false;
}

// shock the patient
double Shockers::shock(){
    if (charged){
        qInfo() << "SHOCKING";
        charged = false;
        return this->power;
    }
    return this->power;
}

// charge the machine
bool Shockers::chargeUP(){
    charged = true;
    return charged;
}

void Shockers::setPower(double power){
    this->power = power;
}

double Shockers::getPower(){return power;}

// check if this part is working
bool Shockers::getWorking(){
    return working;
}

bool Shockers::getCharged(){return charged;}
