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
