#include "GrimoireCalculator.h"
#include <cmath>

GrimoireCalculator::GrimoireCalculator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    currentMagicModified();
    maximumMagicModified();
}

// Update cost for every spell
void GrimoireCalculator::_updateCost()
{
    int M = ui.spinBox_maximum->value();
    ui.lineEdit_cost1->setText(QString::number(std::floor(2 + 0.40 * M)));
    ui.lineEdit_cost2->setText(QString::number(std::floor(10 + 0.60 * M)));
    ui.lineEdit_cost3->setText(QString::number(std::floor(8 + 0.20 * M)));
    ui.lineEdit_cost4->setText(QString::number(std::floor(20 + 0.75 * M)));
    ui.lineEdit_cost5->setText(QString::number(std::floor(10 + 0.10 * M)));
    ui.lineEdit_cost6->setText(QString::number(std::floor(10 + 0.20 * M)));
    ui.lineEdit_cost7->setText(QString::number(std::floor(3 + 0.05 * M)));
    ui.lineEdit_cost8->setText(QString::number(std::floor(20 + 0.10 * M)));
    ui.lineEdit_cost9->setText(QString::number(std::floor(5 + 0.20 * M)));
}

// Update time until replenished
void GrimoireCalculator::_updateTime()
{
    int M = 100;
    if (ui.spinBox_maximum->value() > M)
        M = ui.spinBox_maximum->value();
    double t = 5 * std::sqrt(M) / 9 * (std::sqrt(M) - std::sqrt(ui.spinBox_current->value()));
    double tSec = std::fmod(t,1);
    ui.lineEdit_time->setText(QString::number(t - tSec) + " m " + QString::number(std::floor(tSec * 60)) + " s");
}

// Slot: Current magic is modified
void GrimoireCalculator::currentMagicModified()
{
    if (ui.spinBox_current->value() > ui.spinBox_maximum->value())
        ui.spinBox_current->setValue(ui.spinBox_maximum->value());
    else _updateTime();
}

// Slot: Maximum magic is modified
void GrimoireCalculator::maximumMagicModified()
{
    _updateCost();
    if (ui.spinBox_maximum->value() > 100)
        _updateTime();
}
