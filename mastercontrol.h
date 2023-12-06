#ifndef MASTERCONTROL_H
#define MASTERCONTROL_H

#include <QObject>

class MasterControl : public QObject
{
public:
    MasterControl();
    ~MasterControl();

    void startAED();
    bool diagnostics();
    void firstHalfSteps();

signals:

};

#endif // MASTERCONTROL_H
