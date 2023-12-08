#ifndef HEARTSENSOR_H
#define HEARTSENSOR_H

#include <QObject>

class HeartSensor : public QObject
{
        Q_OBJECT
private:
    bool working;

public:
    HeartSensor();
    bool getWorking(); // check if this part is working

public slots:
    //int getCondition(int i);

signals:
    void sendPEASignal(); // send PEA signal
    void sendAsystoleSignal(); // send Asystole Signal
    void sendVTSignal(); // send VT signal
    void sendVFSignal(); // send VF signal


};

#endif // HEARTSENSOR_H
