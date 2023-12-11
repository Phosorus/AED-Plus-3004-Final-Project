#ifndef MASTERCONTROL_H
#define MASTERCONTROL_H

#include "mainwindow.h"
#include "battery.h"
#include "shockers.h"
#include "compressionsensor.h"
#include "heartsensor.h"
#include "patient.h"

#include <QtDebug>
#include <QObject>
#include <QThread>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <QDateTime>

class MasterControl : public QObject
{
    Q_OBJECT

public:
    MasterControl(Patient*);
    ~MasterControl();

    void delay(int n);

    int diagnostics();
    void firstHalfSteps();
    void analysis();
    void compressions(bool alignment);
    void powerOff();
    void testAED(int i);

    MainWindow* w;
    CompressionSensor* cs;
    HeartSensor* hs;
    Patient* patient;

private slots:
    void startAED();
    void padsApplied();
    void padsAppliedChild();
    void goodCompressions();
    void badCompressions();
    void breaths();
    void shock();
    void changeBattery();

private:
    QDateTime prevCompressionTime;
    QDateTime curCompressionTime;
    bool currentlyShockable = false;
    bool currentlyUnstable = true;
    int numCompressions = 0;
    int numBreaths = 0;
    int numShocks = 0;
    int cprRounds = 0;

    bool isChild = false;
    bool hasPower = false;

    Shockers* shocker;
    Battery* battery;

signals:

};

#endif // MASTERCONTROL_H
