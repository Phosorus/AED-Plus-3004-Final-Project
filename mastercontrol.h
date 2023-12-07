#ifndef MASTERCONTROL_H
#define MASTERCONTROL_H

#include "mainwindow.h"
#include "battery.h"
#include <QObject>
#include <QThread>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

class MasterControl : public QObject
{
    Q_OBJECT

public:
    MasterControl();
    ~MasterControl();

    void delay(int n);

    bool diagnostics();
    void firstHalfSteps();
    void analysis();
    void shock();
    void compressions(bool alignment);
    void breaths();
    void powerOff();

public slots:
    void startAED();
    void padsApplied();

private:
    Battery* battery;
    MainWindow* w;

signals:

};

#endif // MASTERCONTROL_H
