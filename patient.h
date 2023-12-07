#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>

class patient : public QObject
{
    Q_OBJECT
public:
    patient(int currentCondition);

private:
    int currentCondition = 1;

signals:
    void conditionSignal(int condition);

};

#endif // PATIENT_H
