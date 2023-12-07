#include "mastercontrol.h"

MasterControl::MasterControl()
{
     battery = new Battery();
     w = new MainWindow;

     w->show();

     //connect to all the proper buttons, signals, and slots;
     connect(w, SIGNAL(powerOn()), this, SLOT(startAED()));

     connect(w, SIGNAL(), this, SLOT(padsApplied()));
     connect(w, SIGNAL(), this, SLOT(padsApplied()));

}

//Wait for n seconds;
void MasterControl::delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MasterControl::startAED(){
    if(!(diagnostics())){
        //[display] Failure
        //end AED
    }
    else{
        //First half of the AED steps
        firstHalfSteps();
    }
}

//Checks the battery plus each element of the AED.
bool MasterControl::diagnostics(){
    //check battery for sufficient battery power
    if(battery->charge < 95){
        return false;
    }
    //check each component for working

    //if one is false, return false;
    return true;
}

//runs through the first phase of the AED, since they are always consistant and only occur once.
void MasterControl::firstHalfSteps(){
    w->stepIndicator(1);
    delay(3);
    w->stepIndicator(2);
    delay(3);
    w->stepIndicator(3);
}

//called when pads detect being applied to a person
void MasterControl::padsApplied(){
    //display pads applied
    //run analysis
}

void MasterControl::analysis(){
    //analysis phase

    //switch statement
        //if tachycardia
            //display graph
            //shockable
        //if fibri
            //display graph
            //shockable
        //if normmal
            //display graph
            //non-shockable + No cpr
        //if flatline
            //display graph
            //non-shockable + cpr

    //if(shockable)
        //change shockable global variable to TRUE
        //function ends
    //else
        //call CPR function
        //function ends
}

void MasterControl::shock(){
    //if shockable == true
        //deplete battery
        //shocker->chargeUp()
        //shocker->shock()
        //display deliver shock
        //shockable == false;
        //prompt display to deliver CPR
}

void MasterControl::compressions(bool alignment){
    //if compressions global variable == 30:
            //display "move on to breaths"
    //else
        // if(alignment) "good"
            //compressions++;
        //else
            //display "Bad compressions"
}

void MasterControl::breaths(){
    //if(breaths global variable == 2)
        //display "return to analysis
        //return to analysis phase.
}

MasterControl::~MasterControl()
{
    delete battery;
}
