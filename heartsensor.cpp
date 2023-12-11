/*
This class serves as the AED's heart sensor


Important Functions:

getWorking() - used in the AED's initial checkup of all components
getPatientCondition() - Analyzes the patient and determines their heart condition to send the information to master control

*/

#include "heartsensor.h"

HeartSensor::HeartSensor(Patient* patient)
{
    this->patient = patient;
    working = true;
}

// check if this part is working
bool HeartSensor::getWorking(){
    return working;
}

int HeartSensor::getPatientCondition(){
    return this->patient->getHeartCondition();
}
