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
/*
 * Need to create a function that cycles through the AED Process (probably in the AED controller)
*/
void MainWindow::on_btnPowerButton_clicked()
{
    powerOn();
    /*
    Need to check power level
    Only after the power is on can you use the unit
    Second step is to check status of AED
    if power level not sufficient indicate audio msg
    */
}

void MainWindow::lowBattery(){
    ui->lblLED_Display->setStyleSheet("font-weight: bold; font-size: 30px; background-color: rgb(0, 0, 0);border: 2px solid rgb(0,0,0);");
    ui->lblGoodStatus->setStyleSheet("font-weight: bold; font-size: 50px;");
    ui->lblBadStatus->setStyleSheet("font-weight: bold; font-size: 46px; color: rgb(255, 0, 0);");
    ui->lblLED_Display->setAlignment(Qt::AlignCenter);
    ui->lblLED_Display->setText("CHANGE BATTERY");
}
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
void MainWindow::on_btnShockIndicator_clicked()
{
    shock();
}

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
}
void MainWindow::shockReady(){
    ui->btnShockIndicator->setStyleSheet("color: rgb(255, 0, 0); font-size: 45px; font-weight: bold; background-color: rgb(133, 172, 190); border: 4px solid rgb(45, 255, 0); border-radius: 25px;");
    QString s = "Shock Ready!";
    s = "\"" + s +"\"";
    s = "AED: " + s;
    ui->ActionLog->append(s);
}

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

void MainWindow::changeBatteryLevel(int i){
    QString s = "▮";
    s = s +  QString::number(i) +"%";
    ui->lblBatteryDisplay->setText(s);
}

void MainWindow::changeCompressionCount(int i){
    QString s = "Compressions: ";
    s = s +  QString::number(i);
    ui->lblCompressionCount->setText(s);
}
void MainWindow::changeBreathCount(int i){
    QString s = "Breaths: ";
    s = s +  QString::number(i);
    ui->lblBreathCount->setText(s);
}
void MainWindow::changeShockCount(int i){
    QString s = "Shocks: ";
    s = s +  QString::number(i);
    ui->lblShockCount->setText(s);
}

void MainWindow::compressionToggle(bool t){
    if(t==true){
        ui->btnApplyGoodCompression->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(45, 255, 0);border-radius: 6px;background-color: rgb(255, 255, 255);");
        ui->btnApplyBadCompression->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(45, 255, 0);border-radius: 6px;background-color: rgb(255, 255, 255);");
    }else{
        ui->btnApplyGoodCompression->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(175, 193, 204);border-radius: 6px;background-color: rgb(255, 255, 255);");
        ui->btnApplyBadCompression->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(175, 193, 204);border-radius: 6px;background-color: rgb(255, 255, 255);");
    }
}

void MainWindow::breathToggle(bool t){
    if(t==true){
        ui->btnApplyBreathes->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(45, 255, 0);border-radius: 6px;background-color: rgb(255, 255, 255);");
    }else{
        ui->btnApplyBreathes->setStyleSheet("font-size: 13px;color: rgb(0, 0, 0);font-weight: bold;border: 4px solid  rgb(175, 193, 204);border-radius: 6px;background-color: rgb(255, 255, 255);");
    }
}
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


void MainWindow::on_btnCheckPatient_clicked()
{
    QString s = "Are you alright?";
    s = "\"" + s +"\"";
    s = "USER to PATIENT: " + s;
    ui->ActionLog->append(s);
    ui->btnCheckPatient->setEnabled(false);
}


void MainWindow::on_btnCallHelp_clicked()
{
    QString s = "Calls for help";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);
    ui->btnCallHelp->setEnabled(false);
}


void MainWindow::on_btnApplyGoodCompression_clicked()
{
    QString s = "Applies good chest compression";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);
    //Somehow determine compression quality and have AED give feedback
    applyGoodCompressions();
}

void MainWindow::on_btnApplyBadCompression_clicked()
{
    QString s = "Applies bad chest compression";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);
    applyBadCompressions();
}
void MainWindow::on_btnApplyBreathes_clicked()
{
    QString s = "Applies breath";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);
    applyBreaths();
}


void MainWindow::on_btnAttachAdultPads_clicked()
{
    ui->lblAdult->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(45, 255, 0);");
    ui->lblChild->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255);");
    QString s = "Attaches adult pads to patient";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);

    //Maybe update the value of the AED class to reflect what pad is attached
    //send attach symbols
    attachAdultPads();
}


void MainWindow::on_btnAttachChildPads_clicked()
{
    ui->lblAdult->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255);");
    ui->lblChild->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(45, 255, 0);");
    QString s = "Attaches child pads to patient";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);

    attachChildPads();

    //Maybe update the value of the AED class to reflect what pad is attached
}
