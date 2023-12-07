#include "mainwindow.h"
#include "signalanalyser.h"
#include <QtDebug>
#include <QApplication>
#include "mastercontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasterControl* AED = new MasterControl();
    //AED->startAED();

    return a.exec();
}
