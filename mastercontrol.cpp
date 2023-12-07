#include "mastercontrol.h"

MasterControl::MasterControl()
{
     battery = new Battery(100);
     shocker = new Shockers();
     w = new MainWindow;

     hs = new HeartSensor();
     cs = new CompressionSensor();

     w->show();

     //connect to all the proper buttons, signals, and slots;
     connect(w, SIGNAL(powerOn()), this, SLOT(startAED()));

     connect(w, SIGNAL(attachAdultPads()), this, SLOT(padsApplied()));
     //remember to add child pads attachment
     //connect(w, SIGNAL(), this, SLOT(padsApplied()));
     connect(cs, SIGNAL(sendGoodCompressionSignal()), this, SLOT(goodCompressions()));
     connect(cs, SIGNAL(sendBadCompressionSignal()), this, SLOT(badCompressions()));

     connect(cs, SIGNAL(sendBreaths()), this, SLOT(breaths()));

     connect(w, SIGNAL(shock()), this, SLOT(shock()));


     //Connections for testing purposes
     connect(w, SIGNAL(applyCompressions()), cs, SLOT(goodCompressionsSlot()));
     connect(w, SIGNAL(applyBreaths()), cs, SLOT(breathsSlot()));
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
    if(battery->getCharge() < 95){
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
    analysis();
}

//analysis
void MasterControl::analysis(){
    //reset breaths & compressions
    numCompressions = 0;
    numBreaths = 0;

    //analysis phase
    //get current condition
    w->stepIndicator(4);
    delay(3);
    int condition = 4;
    //switch statement
    switch(condition){
        case 1: //tachycardia
            //display tachycardia graph
            currentlyShockable = true;
            currentlyUnstable =  true;
            qDebug() << "tachycardia trriggered";
            break;
        case 2: // fibri
            //display fibri graph
            currentlyShockable = true;
            currentlyUnstable =  true;
            break;
        case 3: //normal
            //display normal graph
            currentlyUnstable =  false;
            break;
        case 4: //asystole
            currentlyUnstable =  true;
            break;
     }

    qDebug() << "analysis over";

    if(currentlyShockable){//user is shockable and therefore unstable.
        //display ask user to shock
        //wait for user to initiate shock
    }
    else if(currentlyUnstable){//user is unstable but non shockable
        //display "user non shockable, proceed to CPR"
        //move directly to CPR
        w->stepIndicator(5);
    }
    else{//user is non-shockable and stable.
        //display "user normal i guess"
        //wait, then re do analysis
        delay(10);
        analysis();
    }

}

void MasterControl::shock(){
    if(currentlyShockable){
        //display shock warning, step away
        shocker->chargeUP();
        battery->deplete(15); //fix to have modular shocks (child/adult)
        shocker->shock();
        //display shock delivered
        //move on to CPR
        w->stepIndicator(5);
    }
    else{
        //display ERROR: Condition is non-shockable, please re-analyse.
    }
}

void MasterControl::goodCompressions(){
    qDebug() << "good compressions triggered";
    compressions(true);
}

void MasterControl::badCompressions(){
    qDebug() << "bad compressions triggered";
    compressions(false);
}

void MasterControl::compressions(bool alignment){
    if(numCompressions >= 30){
        //display "move on to breaths"
        qDebug() << "numCompressions Finished";
    }
    else{
        if(alignment){
            numCompressions++;
        }
        else{
            //display "Bad compressions"
        }
    }
}

void MasterControl::breaths(){
    if(numBreaths >= 2){
        //display return to analysis
        analysis();
    }
    else{
        numBreaths++;
    }
}

MasterControl::~MasterControl()
{
    delete battery;
    delete shocker;
    delete hs;
    delete cs;
}
