#include "mastercontrol.h"

#define CHILD 8
#define MIN_OPERATION 10
#define SUFFICIENT_CPR_ROUNDS 3
#define SUFFICIENT_COMPRESSIONS 5
#define SUFFICIENT_BREATHS 2

#define LOWER_COMPRESSION_RANGE 900
#define UPPER_COMPRESSION_RANGE 2000
MasterControl::MasterControl(Patient* patient)
{
     battery = new Battery(100);
     shocker = new Shockers();
     w = new MainWindow;
     patient = patient;
     hs = new HeartSensor(patient);
     cs = new CompressionSensor();

     w->show();
     connect(w, SIGNAL(powerOn()), this, SLOT(startAED()));

     connect(w, SIGNAL(attachAdultPads()), this, SLOT(padsApplied()));
     connect(w, SIGNAL(attachChildPads()), this, SLOT(padsAppliedChild()));
     connect(w, SIGNAL(sendTestSignal()), this, SLOT(startTest()));

     connect(cs, SIGNAL(sendGoodCompressionSignal()), this, SLOT(goodCompressions()));
     connect(cs, SIGNAL(sendBadCompressionSignal()), this, SLOT(badCompressions()));
     connect(cs, SIGNAL(sendBreaths()), this, SLOT(breaths()));

     connect(w, SIGNAL(applyGoodCompressions()), cs, SLOT(goodCompressionsSlot()));
     connect(w, SIGNAL(applyBadCompressions()), cs, SLOT(badCompressionsSlot()));
     connect(w, SIGNAL(applyBreaths()), cs, SLOT(breathsSlot()));
     connect(w, SIGNAL(shock()), this, SLOT(shock()));


     connect(w, SIGNAL(changeBattery()), this, SLOT(changeBattery()));

}

//Wait for n seconds;
void MasterControl::delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MasterControl::startAED(){
    //User wants to turn AED on
    if(hasPower == false){
        hasPower = true;
        w->changeBatteryLevel(battery->getCharge());
        //If AED does not have sufficient charge
        if(diagnostics()==0){
            w->lowBattery(battery->getCharge());
        }
        //Hardware issue detected
        else if (diagnostics()==1){
            w->statusCheck(false);
        }
        //Good condition to begin
        else{
            //First half of the AED steps
             w->statusCheck(true);
            firstHalfSteps();
        }
    }
    //User wants to turn AED off
    else{
        numBreaths = 0;
        numCompressions = 0;
        numShocks = 0;
        cprRounds = 0;
        hasPower = false;
        w->powerOff();

    }
}

//Checks the battery plus each element of the AED.
int MasterControl::diagnostics(){
    //check battery for sufficient battery power
    if(battery->getCharge() < shocker->getPower()+MIN_OPERATION){
        return 0;
    }
    //check each component for working
    if(shocker->getWorking()==false && w->working==false && cs->getWorking()==false && hs->getWorking()==false){
        return 1;
    }
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

void MasterControl::padsAppliedChild(){
    //change the power to child safe levels
    shocker->setPower(CHILD);
    analysis();
}

//analysis
void MasterControl::analysis(){
    if(diagnostics()==0){
        w->lowBattery(battery->getCharge());
    }
    else{
        //reset breaths & compressions
        numCompressions = 0;
        numBreaths = 0;

        w->changeCompressionCount(numCompressions);
        w->changeBreathCount(numBreaths);
        w->changeShockCount(numShocks);
        //analysis phase
        //get current condition

        int condition = hs->getPatientCondition();

        w->stepIndicator(4);
        delay(3);

        //switch statement
        switch(condition){
            case 1: //tachycardia
                //display tachycardia graph
                w->graphDisplay(4);
                currentlyShockable = true;
                currentlyUnstable =  true;
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
            w->compressionToggle(true);
            w->breathToggle(false);
        }
        else{//user is non-shockable and stable.
            w->aedMessages(8);
            //wait, then re do analysis
            delay(10);
            analysis();
        }
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
            battery->deplete(shocker->shock());
            numShocks++;

            //Update the battery level on AED screen
            w->changeBatteryLevel(battery->getCharge());
            w->changeShockCount(numShocks);

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
        w->aedMessages(9);
    }
}

void MasterControl::goodCompressions(){
    compressions(true);
}

void MasterControl::badCompressions(){
    compressions(false);
}

void MasterControl::compressions(bool alignment){
    if(alignment){
        if(numCompressions==0){
            prevCompressionTime = QDateTime::currentDateTime();
            numCompressions++;
            w->changeCompressionCount(numCompressions);
        }
        else{
            curCompressionTime = QDateTime::currentDateTime();
            //Too fast
            if(prevCompressionTime.msecsTo(curCompressionTime)<=LOWER_COMPRESSION_RANGE){
                w->aedMessages(10);
            }
            //Too slow
            else if (prevCompressionTime.msecsTo(curCompressionTime) >= UPPER_COMPRESSION_RANGE){
                w->aedMessages(11);
            }
            //Good Timing
            else{
                if(numCompressions+1>=SUFFICIENT_COMPRESSIONS){
                    //User UI indicator changes
                    w->stopTimer();
                    w->compressionToggle(false);
                    w->breathToggle(true);

                    //Updates the compression count but also sends AED audio queue to move onto breaths as adequet compression count has been reached
                    numCompressions++;
                    w->changeCompressionCount(numCompressions);
                    w->aedMessages(2);
                }
                else{
                    numCompressions++;
                    w->changeCompressionCount(numCompressions);
                }
            }
            prevCompressionTime = curCompressionTime;
        }

    }
    else{
        //Audio warning for a bad compression being detected
        w->aedMessages(1);
    }


}

void MasterControl::breaths(){
    if(numCompressions<SUFFICIENT_COMPRESSIONS){
        //Send AED message to state not enough compressions have been preformed
        w->aedMessages(3);
    }
    else{
        if(numBreaths+1 == SUFFICIENT_BREATHS){
            //User UI indicator changes
            w->breathToggle(false);

            numBreaths++;
            w->changeBreathCount(numBreaths);
            //if sufficient rounds of CPR has been reached, display return to analysis
            if(cprRounds+1==SUFFICIENT_CPR_ROUNDS){
                cprRounds=0;
                analysis();
            }else{
                cprRounds++;

                numCompressions=0;
                w->changeCompressionCount(numCompressions);
                numBreaths=0;
                w->changeBreathCount(numBreaths);

                w->stepIndicator(5);
                w->compressionToggle(true);
                w->breathToggle(false);

            }
        }
        else{
            numBreaths++;
            w->changeBreathCount(numBreaths);
        }
    }

}

void MasterControl::changeBattery(){
    battery->change();
    numBreaths = 0;
    numCompressions = 0;
    numShocks = 0;
    cprRounds = 0;
    hasPower = false;
    w->powerOff();
}

void MasterControl::startTest(){
    qDebug() << "start test";
    qDebug() << QString::number(w->getTestSelection());
    testAED(w->getTestSelection());
}
void MasterControl::testAED(int i){
    switch(i){
        case 0: //Battery Failure

            //setup battery low power
            battery->deplete(90);

            delay(10);
            w->powerOn();
            delay(5);

            w->powerOff();

        break;
        case 1: //Component Failure

            //setup faulty components
                //

            w->powerOn();
            delay(5);

        break;
        case 2: //Correct Procedure (Shockable)
            delay(5);

            w->on_btnPowerButton_clicked();
            delay(5);

            w->on_btnAttachAdultPads_clicked();
            delay(5);

            w->on_btnShockIndicator_clicked();

            delay(7);

            for(int k = 0; k < SUFFICIENT_CPR_ROUNDS; k++)
            {
                for(int i = 0; i < SUFFICIENT_COMPRESSIONS; i++){
                    w->goodCompressionPressed();
                    //qDebug() << "Triggered";
                    delay(1.1);
                }

                delay(2);

                for(int i = 0; i < SUFFICIENT_BREATHS; i++){
                    w->on_btnApplyBreathes_clicked();
                    delay(1.1);
                }

                delay(2);
            }

            delay(5);

            w->on_btnPowerButton_clicked();
        break;

        case 3: //Correct Procedure (Non-Shockable)
            delay(5);

            w->on_btnPowerButton_clicked();
            delay(5);

            w->on_btnAttachAdultPads_clicked();
            delay(5);

            for(int k = 0; k < SUFFICIENT_CPR_ROUNDS; k++)
            {
                for(int i = 0; i < SUFFICIENT_COMPRESSIONS; i++){
                    w->goodCompressionPressed();
                    //qDebug() << "Triggered";
                    delay(1.1);
                }

                delay(2);

                for(int i = 0; i < SUFFICIENT_BREATHS; i++){
                    w->on_btnApplyBreathes_clicked();
                    delay(1.1);
                }

                delay(2);
            }

            delay(5);

            w->on_btnPowerButton_clicked();
        break;

        case 4: //Correct Procedure (Stable)

            delay(5);

            w->on_btnPowerButton_clicked();
            delay(5);

            w->on_btnAttachAdultPads_clicked();
            delay(5);

            delay(15);

            w->on_btnPowerButton_clicked();

        break;

        case 5: //shockable child
            delay(5);

            w->on_btnPowerButton_clicked();
            delay(5);

            w->on_btnAttachChildPads_clicked();
            delay(5);

            w->on_btnShockIndicator_clicked();

            delay(7);

            for(int k = 0; k < SUFFICIENT_CPR_ROUNDS; k++)
            {
                for(int i = 0; i < SUFFICIENT_COMPRESSIONS; i++){
                    w->goodCompressionPressed();
                    //qDebug() << "Triggered";
                    delay(1.1);
                }

                delay(2);

                for(int i = 0; i < SUFFICIENT_BREATHS; i++){
                    w->on_btnApplyBreathes_clicked();
                    delay(1.1);
                }

                delay(2);
            }

            delay(5);

            w->on_btnPowerButton_clicked();
        break;

        case 6: //pannels disconnected

        break;

        case 7: //depleted to critical  state
            delay(5);

            w->on_btnPowerButton_clicked();
            delay(5);

            w->on_btnAttachChildPads_clicked();
            delay(5);

            w->on_btnShockIndicator_clicked();

            delay(7);

            for(int k = 0; k < SUFFICIENT_CPR_ROUNDS; k++)
            {
                for(int i = 0; i < SUFFICIENT_COMPRESSIONS; i++){
                    w->goodCompressionPressed();
                    //qDebug() << "Triggered";
                    delay(1.1);
                }

                delay(2);

                for(int i = 0; i < SUFFICIENT_BREATHS; i++){
                    w->on_btnApplyBreathes_clicked();
                    delay(1.1);
                }

                delay(2);
            }

            delay(6);

            w->on_btnShockIndicator_clicked();

            delay(7);

            for(int k = 0; k < SUFFICIENT_CPR_ROUNDS; k++)
            {
                for(int i = 0; i < SUFFICIENT_COMPRESSIONS; i++){
                    w->goodCompressionPressed();
                    //qDebug() << "Triggered";
                    delay(1);
                }

                delay(2);

                for(int i = 0; i < SUFFICIENT_BREATHS; i++){
                    w->on_btnApplyBreathes_clicked();
                    delay(1);
                }

                delay(2);
            }

            delay(5);

            w->on_btnShockIndicator_clicked();

            delay(7);

            for(int k = 0; k < SUFFICIENT_CPR_ROUNDS; k++)
            {
                for(int i = 0; i < SUFFICIENT_COMPRESSIONS; i++){
                    w->goodCompressionPressed();
                    //qDebug() << "Triggered";
                    delay(1);
                }

                delay(2);

                for(int i = 0; i < SUFFICIENT_BREATHS; i++){
                    w->on_btnApplyBreathes_clicked();
                    delay(1);
                }

                delay(2);
            }

            delay(5);


            w->on_btnPowerButton_clicked();

            break;


    }
}
MasterControl::~MasterControl()
{
    delete battery;
    delete shocker;
    delete hs;
    delete cs;
}
