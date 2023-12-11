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

// check if this part is working
bool Shockers::getWorking(){
    return working;
}

bool Shockers::getCharged(){return charged;}
