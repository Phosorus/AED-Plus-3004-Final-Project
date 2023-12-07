#include "compressionsensor.h"

CompressionSensor::CompressionSensor()
{
    working = true;

}

// check if this part is working
bool CompressionSensor::getWorking(){
    return working;
}

