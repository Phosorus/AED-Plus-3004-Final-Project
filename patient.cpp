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
