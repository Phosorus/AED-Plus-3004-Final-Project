#ifndef HEARTSENSOR_H
#define HEARTSENSOR_H

#include "patient.h"
#include <QObject>

class HeartSensor : public QObject
{
        Q_OBJECT
private:
    bool working;
    Patient* patient;

public:
    HeartSensor(Patient* patient);
    bool getWorking(); // check if this part is working
    int getPatientCondition(); //get patient condition

public slots:
    //int getCondition(int i);

signals:
    void sendPEASignal(); // send PEA signal
    void sendAsystoleSignal(); // send Asystole Signal
    void sendVTSignal(); // send VT signal
    void sendVFSignal(); // send VF signal
};

#endif // HEARTSENSOR_H
