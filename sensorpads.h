#ifndef SENSORPADS_H
#define SENSORPADS_H

#include <QObject>
#include "heartsensor.h"
#include "compressionsensor.h"

class SensorPads : public QObject
{
    Q_OBJECT
private:
    CompressionSensor* cs;
    HeartSensor* hs;
    bool working;

public:
    SensorPads();
    bool getWorking(); // check if this part is working


public slots:
    void goodCompressionSlot();
    void badCompressionSlot();
    void peaSlot();
    void asystoleSlot();
    void vtSlot();
    void vfSlot();

signals:
    void sendGoodCompressionSignal(); // send good compression signal
    void sendBadCompressionSignal(); // send bad compression signal
    void sendPEASignal(); // send pea singal
    void sendAsystoleSignal(); // send asystoles signal
    void sendVTSignal(); // send vt signal
    void sendVFSignal(); /// sendd vf signal

};

#endif // SENSORPADS_H
