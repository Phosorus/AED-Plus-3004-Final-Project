#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <random>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void stepIndicator(int step);
    void changeBatteryLevel(int i);
    void graphDisplay(int i);
    void statusCheck(bool);
    void shockReady();

public slots:
    void on_btnPowerButton_clicked();
    void on_btnShockIndicator_clicked();


    void on_btnCheckPatient_clicked();
    void on_btnCallHelp_clicked();


    void on_btnApplyGoodCompression_clicked();
    void on_btnApplyBadCompression_clicked();
    void on_btnApplyBreathes_clicked();

    void on_btnAttachAdultPads_clicked();
    void on_btnAttachChildPads_clicked();

signals:
    void powerOn();
    void attachChildPads();
    void attachAdultPads();
    void shock();
    void applyCompressions();
    void applyBreaths();

private:
    Ui::MainWindow *ui;
    int counter;
};
#endif // MAINWINDOW_H
