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
    void _updateCost();
    void _updateTime();

private slots:
    void currentMagicModified();
    void maximumMagicModified();
};
