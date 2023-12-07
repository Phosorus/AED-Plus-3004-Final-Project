#include "sensorpads.h"

// Connect to Heart sensor and Compression sensor signals and slots
SensorPads::SensorPads()
{
    working = true;
    connect(this->cs, SIGNAL(sendGoodCompressionSignal()), this, SLOT(goodCompressionSlot()));
    connect(this->cs, SIGNAL(sendBadCompressionSignal()), this, SLOT(badCompressionSlot()));
    connect(this->hs, SIGNAL(sendPEASignal()), this, SLOT(peaSlot()));
    connect(this->hs, SIGNAL(sendAsystoleSignal()), this, SLOT(asystoleSlot()));
    connect(this->hs, SIGNAL(sendVTSignal()), this, SLOT(vtslot));
    connect(this->hs, SIGNAL(sendVFSignal()), this, SLOT(vfslot));
}

// good compression signal
void SensorPads::goodCompressionSlot(){
    sendGoodCompressionSignal();
}

// bad compression signal
void SensorPads::badCompressionSlot(){
    sendBadCompressionSignal();
}

// PEA signal
void SensorPads::peaSlot(){
    sendPEASignal();
}

// Asystole signal
void SensorPads::asystoleSlot(){
    sendAsystoleSignal();
}

// VT signal
void SensorPads::vtSlot(){
    sendVTSignal();
}

// VF signal
void SensorPads::vfSlot(){
    sendVFSignal();
}

// check if this part is working
bool SensorPads::getWorking(){
    return working;
}
