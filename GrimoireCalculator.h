#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GrimoireCalculator.h"

class GrimoireCalculator : public QMainWindow
{
    Q_OBJECT

public:
    GrimoireCalculator(QWidget *parent = Q_NULLPTR);

private:
    Ui::GrimoireCalculatorClass ui;
    bool _calculate();
    void _updateCost();
    void _updateTime();
    void _activateSpell(int spellCost);
    void _errorDisplay(QString &errorMessage);

private slots:
    void calculatePressed();
    void maxCurrentMagicPressed();
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
