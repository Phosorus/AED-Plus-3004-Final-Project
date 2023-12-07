#ifndef COMPRESSIONSENSOR_H
#define COMPRESSIONSENSOR_H


#include <QObject>


class CompressionSensor : public QObject
{
    Q_OBJECT
private:
    bool working;

public:
    CompressionSensor();
    bool getWorking(); // check if this part is working

public slots:
    void goodCompressionsSlot();
    void badCompressionsSlot();
    void breathsSlot();

signals:
    void sendGoodCompressionSignal(); // send good compression signal
    void sendBadCompressionSignal(); // send bad compression signal
    void sendBreaths();


};

#endif // COMPRESSIONSENSOR_H
