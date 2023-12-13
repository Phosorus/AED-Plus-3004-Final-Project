#ifndef SHOCKERS_H
#define SHOCKERS_H


class Shockers
{
private:
    bool charged;
    double power = 40;
public:
    Shockers();
    double shock(); // shock the patient
    bool chargeUP(); // charge the machine
    bool getCharged();
    bool getWorking(); // check if this part is working
    double getPower();
    bool working;
    void setPower(double power);
};

#endif // SHOCKERS_H
