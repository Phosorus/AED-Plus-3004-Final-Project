#ifndef BATTERY_H
#define BATTERY_H


class Battery
{
public:
    Battery(int n);
    void change();
    int deplete(int n);
    int getCharge();

private:
    int charge;
};

#endif // BATTERY_H
