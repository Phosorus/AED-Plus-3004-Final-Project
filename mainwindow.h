#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <random>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void delay(int n);
    void lowBattery(int c);
    void powerOff();
    void aedMessages(int i);
    void stepIndicator(int step);
    void changeBatteryLevel(int i);
    void compressionToggle(bool t);
    void changeCompressionCount(int i);
    void breathToggle(bool t);
    void changeBreathCount(int i);
    void graphDisplay(int i);
    void statusCheck(bool);
    void shockReady();
    void changeShockCount(int i);
    void resetUI();
    bool working;

public slots:
    void on_btnPowerButton_clicked();
    void on_btnShockIndicator_clicked();


    void on_btnCheckPatient_clicked();
    void on_btnCallHelp_clicked();

    void updateTimer();
    void stopTimer();
    void on_btnApplyBadCompression_clicked();
    void on_btnApplyBreathes_clicked();
    void goodCompressionPressed();
    void on_btnAttachAdultPads_clicked();
    void on_btnAttachChildPads_clicked();

signals:
    void powerOn();
    void attachChildPads();
    void attachAdultPads();
    void shock();
    void applyGoodCompressions();
    void applyBadCompressions();
    void applyBreaths();
    void changeBattery();

private slots:
    void on_btnChangeBattery_clicked();

private:
    Ui::MainWindow *ui;
    int counter;
    QTimer *timer;
    QTime startTime;
};
#endif // MAINWINDOW_H
