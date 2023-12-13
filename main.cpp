#include "mainwindow.h"
#include <QtDebug>
#include <QApplication>
#include "mastercontrol.h"
#include "patient.h"
#include "string.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Patient *p1 = new Patient(1, false);
    Patient *p2 = new Patient(2, true);
    Patient *p3 = new Patient(3, false);
    Patient *p4 = new Patient(4, true);
    Patient *p5 = new Patient(3, false);
    Patient *p6 = new Patient(1, true);
    Patient *p7 = new Patient(0, false);

    Patient** patientList = new Patient*[7];

    patientList[0] = p1;
    patientList[1] = p2;
    patientList[2] = p3;
    patientList[3] = p4;
    patientList[4] = p5;
    patientList[5] = p6;
    patientList[6] = p7;

    int currentPatient = 1;

    MasterControl* AED = new MasterControl(patientList[currentPatient]);

    //delete[] patientList;
    //delete AED;
    return a.exec();
}
