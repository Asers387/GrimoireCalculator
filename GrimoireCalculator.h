#ifndef GRIMOIRECALCULATOR_H
#define GRIMOIRECALCULATOR_H

#include <QtWidgets/QMainWindow>
#include <cmath>
#include <qmessagebox.h>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <QCloseEvent>
#include <thread>
#include "ui_GrimoireCalculator.h"

class GrimoireCalculator : public QMainWindow
{
    Q_OBJECT

public:
    GrimoireCalculator(QWidget *parent = Q_NULLPTR);

private:
    Ui::GrimoireCalculatorClass ui;

    int timeHour;
    int timeMin;
    int timeSec;
    bool realTimeActivated = false;
    std::thread realTimeThread;

    bool _calculate();
    void _updateCost();
    void _updateTime();
    void _updateTimeFormat();
    void _activateSpell(int spellCost);
    void _errorDisplay(QString &errorMessage);
    void _readState();
    void _saveState();
    void _realTime();

    void closeEvent(QCloseEvent *event);

private slots:
    void calculatePressed();
    void maxCurrentMagicPressed();
    void realTimePressed();
    void helpPressed();
    void aboutPressed();
    void spell1Pressed();
    void spell2Pressed();
    void spell3Pressed();
    void spell4Pressed();
    void spell5Pressed();
    void spell6Pressed();
    void spell7Pressed();
    void spell8Pressed();
    void spell9Pressed();
};

#endif // GRIMOIRECALCULATOR_H
