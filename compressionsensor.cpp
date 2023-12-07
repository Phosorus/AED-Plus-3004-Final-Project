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
