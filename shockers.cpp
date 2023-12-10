#include "shockers.h"
#include <QDebug>

Shockers::Shockers()
{
    charged = false;
}

// shock the patient
bool Shockers::shock(){
    if (charged){
        qInfo() << "SHOCKING";
        charged = false;
        return true;
    }
    return false;
}

// charge the machine
bool Shockers::chargeUP(){
    charged = true;
    return charged;
}

// check if this part is working
bool Shockers::getWorking(){
    return working;
}

bool Shockers::getCharged(){return charged;}
