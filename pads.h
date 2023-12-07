#ifndef PADS_H
#define PADS_H

#include <QObject>

class Pads : public QObject
{
    Q_OBJECT
private:
    bool working;

public:
    Pads();
    bool checkElectrodePads(); // check if electrods are attached to patient and AED
    bool getWorking(); // check if this part is working

signals:
    void sendElectrodesSignal();

};

#endif // PADS_H
