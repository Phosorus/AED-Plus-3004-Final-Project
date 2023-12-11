#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->grpUserActions->hide();
    ui->grpPadOptions->hide();
    ui->grpTreatmentOptions->hide();
    ui->lblStep1->setEnabled(false);
    ui->lblStep2->setEnabled(false);
    ui->lblStep3->setEnabled(false);
    ui->lblStep4->setEnabled(false);
    ui->lblStep5->setEnabled(false);
    ui->lblStep6->setEnabled(false);
    counter = 0;
    isWorking = true;
    connect(ui->btnApplyGoodCompression, SIGNAL(clicked()), this, SLOT(goodCompressionPressed()));

    // Initialize timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Wait for n seconds;
void MainWindow::delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//Sends a signal to the master control that the power button has been pressed (turn on/ turn off)
void MainWindow::on_btnPowerButton_clicked()
{
    QString s = "Powering On!";
    s = "\"" + s +"\"";
    s = "AED: " + s;
    ui->ActionLog->append(s);

    powerOn();
}

//Recieves signal from master control and resets the UI for the case of power off
void MainWindow::powerOff(){
    QString s = "Powering Off!";
    s = "\"" + s +"\"";
    s = "AED: " + s;
    ui->ActionLog->append(s);

    resetUI();
}

//Recieves signal from master control and displays appropriate visuals for the case of 'low battery'
void MainWindow::lowBattery(int c){
    QString s = "▯";
    s = s +  QString::number(c) +"%";
    ui->lblBatteryDisplay->setText(s);

    resetUI();

    ui->lblLED_Display->setStyleSheet("font-weight: bold; font-size: 30px; background-color: rgb(0, 0, 0);border: 2px solid rgb(0,0,0);");
    ui->lblGoodStatus->setStyleSheet("font-weight: bold; font-size: 50px;");
    ui->lblBadStatus->setStyleSheet("font-weight: bold; font-size: 46px; color: rgb(255, 0, 0);");
    ui->lblLED_Display->setAlignment(Qt::AlignCenter);
    ui->lblLED_Display->setText("CHANGE BATTERY");
}

//Helper function called to reset the majority of the UI to base state
void MainWindow::resetUI(){
    ui->lblStep1->setEnabled(false);
    ui->lblStep2->setEnabled(false);
    ui->lblStep3->setEnabled(false);
    ui->lblStep4->setEnabled(false);
    ui->lblStep5->setEnabled(false);
    ui->lblStep6->setEnabled(false);
    ui->lblStep1->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
    ui->lblStep2->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
    ui->lblStep3->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
    ui->lblStep4->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
    ui->lblStep5->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
    ui->lblStep6->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
    ui->lblAdult->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255);");
    ui->lblAdult->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255);");

    ui->lblGoodStatus->setStyleSheet("font-weight: bold; font-size: 50px;");
    ui->lblBadStatus->setStyleSheet("font-weight: bold; font-size: 46px;");
    ui->lblBatteryDisplay->clear();
    ui->lblShockCount->clear();
    ui->lblCompressionCount->clear();
    ui->lblBreathCount->clear();
    ui->lblLED_Display->clear();
    ui->lblHeartSignal->clear();
    compressionToggle(false);
    breathToggle(false);
    ui->btnShockIndicator->setStyleSheet("color: rgb(255, 0, 0); font-size: 45px; font-weight: bold; background-color: rgb(133, 172, 190); border: 4px solid rgb(175, 193, 204); border-radius: 25px;");
    ui->grpPadOptions->hide();
    ui->grpTreatmentOptions->hide();
}

//Recieves a value from the master control depending on operational status. Updates the appropriate visuals to reflect this
void MainWindow::statusCheck(bool operational){
    if(operational){
        ui->lblGoodStatus->setStyleSheet("font-weight: bold; font-size: 50px; color: rgb(45, 255, 0);");
        ui->lblBadStatus->setStyleSheet("font-weight: bold; font-size: 46px;");

        QString s = "Automatic Defibrilator Unit OK!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    else{
        ui->lblGoodStatus->setStyleSheet("font-weight: bold; font-size: 50px;");
        ui->lblBadStatus->setStyleSheet("font-weight: bold; font-size: 46px; color: rgb(255, 0, 0);");
        ui->lblLED_Display->setStyleSheet("font-weight: bold; font-size: 30px; background-color: rgb(0, 0, 0);border: 2px solid rgb(0,0,0);");
        ui->lblLED_Display->setAlignment(Qt::AlignCenter);
        ui->lblLED_Display->setText("ERROR!");
        QString s = "Automatic Defibrilator Unit Error!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
}

//Sends a signal to the master control to initiate a shock to the patient
void MainWindow::on_btnShockIndicator_clicked(){shock();}

//Takes a value from the master control and displays the appropriate audio message into the ActionLog
void MainWindow::aedMessages(int i){
    if(i == 1){
        QString s = "Poor compression detected, please adjust!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    if(i == 2){
        QString s = "Compression set complete! Please apply 2 breaths!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    if(i == 3){
        QString s = "Not enough compressions detected. Please apply compressions first!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    if(i == 4){
        QString s = "Shock is advised! Please iniate shock!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    if(i == 5){
        QString s = "Non-shockable treatment! Please iniate CPR!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    if(i == 6){
        ui->btnShockIndicator->setEnabled(false);
        QString s = "STAND CLEAR! DO NOT touch patient!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
        delay(1);

        s = "Shock will be delivered in";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);

        delay(1);
        s = "3";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);

        delay(1);
        s = "2";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);

        delay(1);
        s = "1";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);

        delay(1);
        s = "Shock has been delivered!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);

        ui->btnShockIndicator->setEnabled(true);
    }
    if(i == 7){
        QString s = "Shockers are not charged!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    if(i==8){
        QString s = "Patient appears to be stable!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    if(i==9){
        QString s = "ERROR: Condition is non-shockable, please re-analyse";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    if(i==10){
        QString s = "Poor compression detected, too fast!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    if(i==11){
        QString s = "Poor compression detected, too slow!";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
}

//Signal from the master control which updates the UI to reflect the shock pads are ready
void MainWindow::shockReady(){
    ui->btnShockIndicator->setStyleSheet("color: rgb(255, 0, 0); font-size: 45px; font-weight: bold; background-color: rgb(133, 172, 190); border: 4px solid rgb(45, 255, 0); border-radius: 25px;");
    QString s = "Shock Ready!";
    s = "\"" + s +"\"";
    s = "AED: " + s;
    ui->ActionLog->append(s);
}

//Takes a value from the master control and displays the corresponding graph to reflect the heartsensor's information
void MainWindow::graphDisplay(int i){
    if(i==0){
        ui->lblLED_Display->clear();
    }
    else if(i==1){
        QPixmap image(":/assets/Sinus.png");
        ui->lblLED_Display->setPixmap(image);
        ui->lblHeartSignal->setText("Sinus Rhythm");
    }
    else if(i==2){
        QPixmap image(":/assets/Asystole.png");
        ui->lblLED_Display->setPixmap(image);
        ui->lblHeartSignal->setText("Asystole");
    }
    else if(i==3){
        QPixmap image(":/assets/fibrillation.png");
        ui->lblLED_Display->setPixmap(image);
        ui->lblHeartSignal->setText("Ventricular Fibrillation");
    }
    else if(i==4){
        QPixmap image(":/assets/tachycardia.png");
        ui->lblLED_Display->setPixmap(image);
        ui->lblHeartSignal->setText("Ventricular Tachycardia");
    }
}

//Takes a value from the master control to update the battery percentage of the AED
void MainWindow::changeBatteryLevel(int i){
    QString s = "▮";
    s = s +  QString::number(i) +"%";
    ui->lblBatteryDisplay->setText(s);
}

//Takes in a value from the master control and displays the current number of good compressions performed
void MainWindow::changeCompressionCount(int i){
    QString s = "Compressions: ";
    s = s +  QString::number(i);
    ui->lblCompressionCount->setText(s);
}

//Takes in a value from the master control and displays the current number of breaths performed
void MainWindow::changeBreathCount(int i){
    QString s = "Breaths: ";
    s = s +  QString::number(i);
    ui->lblBreathCount->setText(s);
}

//Takes in a value from the master control and displays the current number of shocks
void MainWindow::changeShockCount(int i){
    QString s = "Shocks: ";
    s = s +  QString::number(i);
    ui->lblShockCount->setText(s);
}

//Takes a value from the master control and toggles the indicator around the user's action button to apply compressions
void MainWindow::compressionToggle(bool t){
    if(t==true){
        ui->btnApplyGoodCompression->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(45, 255, 0);border-radius: 6px;background-color: rgb(255, 255, 255);");
        ui->btnApplyBadCompression->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(45, 255, 0);border-radius: 6px;background-color: rgb(255, 255, 255);");
    }else{
        ui->btnApplyGoodCompression->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(175, 193, 204);border-radius: 6px;background-color: rgb(255, 255, 255);");
        ui->btnApplyBadCompression->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(175, 193, 204);border-radius: 6px;background-color: rgb(255, 255, 255);");
    }
}

//Takes a value from the master control and toggles the indicator around the user's action button to apply breath
void MainWindow::breathToggle(bool t){
    if(t==true){
        ui->btnApplyBreathes->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(45, 255, 0);border-radius: 6px;background-color: rgb(255, 255, 255);");
    }else{
        ui->btnApplyBreathes->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(175, 193, 204);border-radius: 6px;background-color: rgb(255, 255, 255);");
    }
}

//Takes a value from the master control and toggles the appropriate UI elements for each AED step. Displays the audio messages into ActionLog
void MainWindow::stepIndicator(int i){
    if(i==1){
        ui->grpUserActions->show();
        ui->grpPadOptions->hide();
        ui->grpTreatmentOptions->hide();
        ui->btnCheckPatient->show();
        ui->btnCallHelp->hide();
        ui->lblStep1->setEnabled(true);
        ui->lblStep2->setEnabled(false);
        ui->lblStep3->setEnabled(false);
        ui->lblStep4->setEnabled(false);
        ui->lblStep5->setEnabled(false);
        ui->lblStep6->setEnabled(false);
        ui->lblStep1->setStyleSheet("border: 4px solid  rgb(45, 255, 0); border-radius: 6px;");
        ui->lblStep2->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep3->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep4->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep5->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep6->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        QString s = "Check responsiveness";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    else if(i==2){
        ui->btnCheckPatient->hide();
        ui->btnCallHelp->show();
        ui->lblStep1->setEnabled(false);
        ui->lblStep2->setEnabled(true);
        ui->lblStep3->setEnabled(false);
        ui->lblStep4->setEnabled(false);
        ui->lblStep5->setEnabled(false);
        ui->lblStep6->setEnabled(false);
        ui->lblStep2->setStyleSheet("border: 4px solid  rgb(45, 255, 0); border-radius: 6px;");
        ui->lblStep1->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep3->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep4->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep5->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep6->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        QString s = "Call for help";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    else if(i==3){
        ui->grpPadOptions->show();
        ui->grpTreatmentOptions->hide();
        ui->btnCallHelp->hide();
        ui->lblStep1->setEnabled(false);
        ui->lblStep2->setEnabled(false);
        ui->lblStep3->setEnabled(true);
        ui->lblStep4->setEnabled(false);
        ui->lblStep5->setEnabled(false);
        ui->lblStep6->setEnabled(false);
        ui->lblStep3->setStyleSheet("border: 4px solid  rgb(45, 255, 0); border-radius: 6px;");
        ui->lblStep2->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep1->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep4->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep5->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep6->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        QString s = "Attach defib pads to patient's bare chest";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    else if(i==4){
        ui->lblStep1->setEnabled(false);
        ui->lblStep2->setEnabled(false);
        ui->lblStep3->setEnabled(false);
        ui->lblStep4->setEnabled(true);
        ui->lblStep5->setEnabled(false);
        ui->lblStep6->setEnabled(false);
        ui->lblStep4->setStyleSheet("border: 4px solid  rgb(45, 255, 0); border-radius: 6px;");
        ui->lblStep2->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep3->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep1->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep5->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep6->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        QString s = "Dont't touch patient! Analyzing";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
    else if(i==5){
        ui->grpPadOptions->hide();
        ui->grpTreatmentOptions->show();
        ui->lblStep1->setEnabled(false);
        ui->lblStep2->setEnabled(false);
        ui->lblStep3->setEnabled(false);
        ui->lblStep4->setEnabled(false);
        ui->lblStep5->setEnabled(true);
        ui->lblStep6->setEnabled(true);
        ui->lblStep5->setStyleSheet("border: 4px solid  rgb(45, 255, 0); border-radius: 6px;");
        ui->lblStep6->setStyleSheet("border: 4px solid  rgb(45, 255, 0); border-radius: 6px;");
        ui->lblStep2->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep3->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep4->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep1->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->btnShockIndicator->setStyleSheet("color: rgb(255, 0, 0); font-size: 45px; font-weight: bold; background-color: rgb(133, 172, 190); border: 4px solid rgb(175, 193, 204); border-radius: 25px;");
        QString s = "Start CPR";
        s = "\"" + s +"\"";
        s = "AED: " + s;
        ui->ActionLog->append(s);
    }
}

//User's action button to check up on the patient. Displays the audio message into ActionLog
void MainWindow::on_btnCheckPatient_clicked()
{
    QString s = "Are you alright?";
    s = "\"" + s +"\"";
    s = "USER to PATIENT: " + s;
    ui->ActionLog->append(s);
    ui->btnCheckPatient->setEnabled(false);
}

//User's action button to call for help. Displays the audio message into ActionLog
void MainWindow::on_btnCallHelp_clicked()
{
    QString s = "Calls for help";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);
    ui->btnCallHelp->setEnabled(false);
}

//User's action button to perform a good compression. Also displays the time between 'good compressions'
void MainWindow::goodCompressionPressed() {
    QString s = "Applies good chest compression";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);
    //Somehow determine compression quality and have AED give feedback

    timer->start(1);
    startTime = QTime::currentTime();

    applyGoodCompressions();
}

//Helper function for goodCompressionPressed that keeps track of time in milliseconds between button presses
void MainWindow::updateTimer() {
    QTime currentTime = QTime::currentTime();
    int elapsed = startTime.msecsTo(currentTime); // Calculate elapsed seconds
    QString s = "Good Compression (" + QString::number(elapsed) + " ms)";

    ui->btnApplyGoodCompression->setText(QString(s));
}

//Helper function used by MasterControl on the last compression of the CPR set to stop timer
void MainWindow::stopTimer(){
    timer->stop();
    ui->btnApplyGoodCompression->setText("Good Compression");
}

//User's action button to perform a bad compression.
void MainWindow::on_btnApplyBadCompression_clicked()
{
    QString s = "Applies bad chest compression";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);

    applyBadCompressions();
}

//User's action button to perform a breath.
void MainWindow::on_btnApplyBreathes_clicked()
{
    QString s = "Applies breath";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);
    applyBreaths();
}

//User's action button to attach adult pads to patient. Updates the visual on AED to reflect this
void MainWindow::on_btnAttachAdultPads_clicked()
{
    ui->lblAdult->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(45, 255, 0);");
    ui->lblChild->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255);");
    QString s = "Attaches adult pads to patient";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);

    attachAdultPads();
}

//User's action button to attach child pads to patient. Updates the visual on AED to reflect this
void MainWindow::on_btnAttachChildPads_clicked()
{
    ui->lblAdult->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255);");
    ui->lblChild->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(45, 255, 0);");
    QString s = "Attaches child pads to patient";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);

    attachChildPads();
}

//User's action button to change the battery
void MainWindow::on_btnChangeBattery_clicked(){changeBattery();}

