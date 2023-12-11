#ifndef PATIENT_H
#define PATIENT_H

#define TACHY = 1;
#define FIBRI = 2;
#define NORMAL = 3;
#define ASYST = 4;

class Patient
{
public:
    Patient(int condition, bool child);

    int getHeartCondition();
    int setHeartCondition(int condition);

private:
    int condition;
    bool child;
};

#endif // PATIENT_H
