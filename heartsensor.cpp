#include "heartsensor.h"

HeartSensor::HeartSensor()
{
    working = true;
}

// check if this part is working
bool HeartSensor::getWorking(){
    return working;
}
