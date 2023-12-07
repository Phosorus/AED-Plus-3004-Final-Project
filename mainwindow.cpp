#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Need to create a function that cycles through the AED Process (probably in the AED controller)
*/
void MainWindow::on_btnPowerButton_clicked()
{

    /*
    Need to check power level
    Only after the power is on can you use the unit
    Second step is to check status of AED
    */

    /*if power level not sufficient indicate audio msg

    QString s = "Change batteries";
    s = "\"" + s +"\"";
    s = "AED: " + s;
    ui->ActionLog->append(s);

    */

    powerOn();
}

void MainWindow::on_btnShockIndicator_clicked()
{
    //Using this as a testing function for now
    counter++;
    stepIndicator(counter);
    if(counter == 5){
        counter = 0;
    }
    /*
    Need to add colour changing for the ready charge and probably audio queue
    */

}

void MainWindow::on_btnStatus_clicked()
{
    //Administer self test

    //if unit is good to go

    QString s = "Automatic Defibrilator. Unit OK!";
    s = "\"" + s +"\"";
    s = "AED: " + s;
    ui->ActionLog->append(s);

    //if unit is not good
    //output indicator
}
void MainWindow::stepIndicator(int i){
    if(i==1){
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
        ui->lblStep5->setStyleSheet("border: 4px solid  rgb(45, 255, 0); border-radius: 6px;");
        ui->lblStep6->setStyleSheet("border: 4px solid  rgb(45, 255, 0); border-radius: 6px;");
        ui->lblStep2->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep3->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep4->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
        ui->lblStep1->setStyleSheet("border: 4px solid  rgb(175, 193, 204); border-radius: 6px;");
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
}


void MainWindow::on_btnCallHelp_clicked()
{
    QString s = "Calls for help";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);
}


void MainWindow::on_btnApplyCompressions_clicked()
{
    QString s = "Applies 1 chest compressions";
    s = "*" + s +"*";
    s = "USER: " + s;
    ui->ActionLog->append(s);
    //Somehow determine compression quality and have AED give feedback

    applyCompressions();
}

void MainWindow::on_btnApplyBreathes_clicked()
{
    QString s = "Applies 2 breathes";
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

    //Maybe update the value of the AED class to reflect what pad is attached
}

