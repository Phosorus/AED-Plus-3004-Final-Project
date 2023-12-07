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

signals:
    void sendGoodCompressionSignal(); // send good compression signal
    void sendBadCompressionSignal(); // send bad compression signal


};

#endif // COMPRESSIONSENSOR_H
