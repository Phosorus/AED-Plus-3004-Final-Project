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

     connect(w, SIGNAL(applyGoodCompressions()), cs, SLOT(goodCompressionsSlot()));
     connect(w, SIGNAL(applyBadCompressions()), cs, SLOT(badCompressionsSlot()));
     connect(w, SIGNAL(applyBreaths()), cs, SLOT(breathsSlot()));
     connect(w, SIGNAL(shock()), this, SLOT(shock()));

}

//Wait for n seconds;
void MasterControl::delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MasterControl::startAED(){
    w->changeBatteryLevel(battery->getCharge());
    if(diagnostics()==0){
        w->lowBattery();
    }
    else if (diagnostics()==1){
        w->statusCheck(false);
    }
    else{
        //First half of the AED steps
         w->statusCheck(true);
        firstHalfSteps();
    }
}

//Checks the battery plus each element of the AED.
int MasterControl::diagnostics(){
    //check battery for sufficient battery power
    if(battery->getCharge() < 60){
        return 0;
    }
    //check each component for working

    //if one is false, return false;
    return 2;
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

    w->changeCompressionCount(numCompressions);
    w->changeBreathCount(numBreaths);
    //analysis phase
    //get current condition
    w->stepIndicator(4);
    delay(3);
    int condition = 1;
    //switch statement
    switch(condition){
        case 1: //tachycardia
            //display tachycardia graph
            w->graphDisplay(4);
            currentlyShockable = true;
            currentlyUnstable =  true;
            qDebug() << "tachycardia triggered";
            break;
        case 2: // fibri
            //display fibri graph
            w->graphDisplay(3);
            currentlyShockable = true;
            currentlyUnstable =  true;
            break;
        case 3: //normal
            //display normal graph
            w->graphDisplay(1);
            currentlyUnstable =  false;
            break;
        case 4: //asystole
            w->graphDisplay(2);
            currentlyUnstable =  true;
            break;
     }

    qDebug() << "analysis over";

    if(currentlyShockable){//user is shockable and therefore unstable.
        //display ask user to shock
        w->aedMessages(4);
        //Primes shock pads and waits for user to initiate shock
        shocker->chargeUP();
        w->shockReady();
    }
    else if(currentlyUnstable){//user is unstable but non shockable
        //display "user non shockable, proceed to CPR"
        w->aedMessages(5);
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
    //Check for sufficient battery?
    if(currentlyShockable){
        //If shocker is primed and has charged
        if(shocker->getCharged()){
            //display shock warning, step away
            w->aedMessages(6);

            //Performs shock
            battery->deplete(15); //fix to have modular shocks (child/adult)
            shocker->shock();

            //Update the battery level on AED screen
            w->changeBatteryLevel(battery->getCharge());

            //move on to CPR
            w->stepIndicator(5);
            w->compressionToggle(true);
            w->breathToggle(false);
        }
        else{
            w->aedMessages(7);
        }
    }
    else{
        //display ERROR: Condition is non-shockable, please re-analyse.
    }
}

void MasterControl::goodCompressions(){
    compressions(true);
}

void MasterControl::badCompressions(){
    compressions(false);
}

void MasterControl::compressions(bool alignment){
    if(alignment && numCompressions+1 >= 30){
        //User UI indicator changes
        w->compressionToggle(false);
        w->breathToggle(true);

        //Updates the compression count but also sends AED audio queue to move onto breaths as adequet compression count has been reached
        numCompressions++;
        w->changeCompressionCount(numCompressions);
        w->aedMessages(2);
    }
    else{
        if(alignment){
            numCompressions++;
            w->changeCompressionCount(numCompressions);
        }
        else{
            //Audio warning for a bad compression being detected
            w->aedMessages(1);
        }
    }
}

void MasterControl::breaths(){
    if(numCompressions<30){
        //Send AED message to state not enough compressions have been preformed
        w->aedMessages(3);
    }
    else{
        if(numBreaths+1 == 2){
            //User UI indicator changes
            w->breathToggle(false);

            numBreaths++;
            w->changeBreathCount(numBreaths);
            //display return to analysis
            analysis();
        }
        else{
            numBreaths++;
            w->changeBreathCount(numBreaths);
        }
    }

}

MasterControl::~MasterControl()
{
    delete battery;
    delete shocker;
    delete hs;
    delete cs;
}
