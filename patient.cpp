/*
This class serves as the Patient the AED/User are serving

Private Members:

condition - the heart condition they have
child - true if they are a child

*/
#include "patient.h"

Patient::Patient(int condition, bool child)
{
    this->condition = condition;
    this->child = child;
}

int Patient::getHeartCondition(){
    return this->condition;
}

int Patient::setHeartCondition(int condition){
    this->condition = condition;
    return this->condition;
}
