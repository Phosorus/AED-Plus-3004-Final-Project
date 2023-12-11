/*
This class serves as the AED's compression sensor

Important Functions:

getWorking() - used in the AED's initial checkup of all components
goodCompressionsSlot() - sends a signal to the mastercontrol when it detects a user performing a good quality compression
badCompressionsSlot() - sends a signal to the mastercontrol when it detects a user performing a poor quality compression
breathsSlot() - - sends a signal to the mastercontrol when it detects a user performing a breath on patient
*/
#include "compressionsensor.h"

CompressionSensor::CompressionSensor()
{
    working = true;

}

// check if this part is working
bool CompressionSensor::getWorking(){
    return working;
}

void CompressionSensor::goodCompressionsSlot(){
    sendGoodCompressionSignal();

}

void CompressionSensor::badCompressionsSlot(){
    sendBadCompressionSignal();
}

void CompressionSensor::breathsSlot(){
    sendBreaths();
}
