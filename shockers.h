#ifndef SHOCKERS_H
#define SHOCKERS_H


class Shockers
{
private:
    bool charged;
    bool working;
public:
    Shockers();
    bool shock(); // shock the patient
    bool chargeUP(); // charge the machine
    bool getCharged();
    bool getWorking(); // check if this part is working
};

#endif // SHOCKERS_H
