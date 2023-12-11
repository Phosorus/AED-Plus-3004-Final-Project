#ifndef HEARTSENSOR_H
#define HEARTSENSOR_H

#include "patient.h"
#include <QObject>

class HeartSensor : public QObject
{
        Q_OBJECT
private:
    Patient* patient;

public:
    HeartSensor(Patient* patient);
    bool working;
    bool getWorking(); // check if this part is working
    int getPatientCondition(); //get patient condition
};

#endif // HEARTSENSOR_H
