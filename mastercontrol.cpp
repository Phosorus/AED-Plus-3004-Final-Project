#include "mastercontrol.h"

MasterControl::MasterControl()
{

}
//Display
void MasterControl::startAED(){
    if(!(diagnostics())){
        //[display] Failure
        //end AED
    }
    else{
        //First half of the AED steps
        firstHalfSteps();
    }



    //Call StepIndicator(1)
    //Call stepIndicator(2)
    //Call stepIndicator(3)
        //check for pads, wait until attached

    //Attaching pads trigger next process
    //Call stepIndicator(4)
        //Update heart beat graph
        //If shockable, do shock

    //Call stepindicator(5)
    //Do compressions
    //do breath

    //Go back to analysis




    //TURN OFF MACHINE
}

//Checks the battery plus each element of the AED.
bool MasterControl::diagnostics(){
    //check battery for sufficient battery power
    //check each component for working
    //if one is false, return false;
    return true;
}

void MasterControl::firstHalfSteps(){
    //stepIndicator1
    //stepIndicator2
    //stepIndicator3
    //Function ends here.
}

void analysis(){

}

MasterControl::~MasterControl()
{

}
