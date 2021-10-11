#include "GrimoireCalculator.h"
#include <cmath>
#include <qmessagebox.h>
#include <string>

GrimoireCalculator::GrimoireCalculator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QAction *calculateAction = ui.menuBar->addAction("Calculate");
    connect(calculateAction, SIGNAL(triggered()), this, SLOT(calculatePressed()));
    QAction* maxCurrentMagicAction = ui.menuBar->addAction("Max Current Magic");
    connect(maxCurrentMagicAction, SIGNAL(triggered()), this, SLOT(maxCurrentMagicPressed()));
    QAction* helpAction = ui.menuBar->addAction("Help");
    connect(helpAction, SIGNAL(triggered()), this, SLOT(helpPressed()));
    QAction* aboutAction = ui.menuBar->addAction("About");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutPressed()));

    _calculate();
}

/*
 * Validates current magic and calculates time and costs
 * If invalid, displays error message and returns false ; else returns true.
 */
bool GrimoireCalculator::_calculate()
{
    if (ui.spinBox_current->value() <= ui.spinBox_maximum->value())
    {
        _updateCost();
        _updateTime();
        return true;
    }
    else
    {
        _errorDisplay(QString::fromStdString("Current magic is superior to maximum!"));
        return false;
    }
}

// Update cost for every spell
void GrimoireCalculator::_updateCost()
{
    int maxMagic = ui.spinBox_maximum->value();
    ui.spinBox_cost1->setValue(std::floor(2 + 0.40 * maxMagic));
    ui.spinBox_cost2->setValue(std::floor(10 + 0.60 * maxMagic));
    ui.spinBox_cost3->setValue(std::floor(8 + 0.20 * maxMagic));
    ui.spinBox_cost4->setValue(std::floor(20 + 0.75 * maxMagic));
    ui.spinBox_cost5->setValue(std::floor(10 + 0.10 * maxMagic));
    ui.spinBox_cost6->setValue(std::floor(10 + 0.20 * maxMagic));
    ui.spinBox_cost7->setValue(std::floor(3 + 0.05 * maxMagic));
    ui.spinBox_cost8->setValue(std::floor(20 + 0.10 * maxMagic));
    ui.spinBox_cost9->setValue(std::floor(5 + 0.20 * maxMagic));
}

// Update time until replenished
void GrimoireCalculator::_updateTime()
{
    int maxMagic = 100;
    if (ui.spinBox_maximum->value() > maxMagic)
        maxMagic = ui.spinBox_maximum->value();
    double time = 5 * std::sqrt(maxMagic) / 9 * (std::sqrt(ui.spinBox_maximum->value()) - std::sqrt(ui.spinBox_current->value()));
    double timeHour = std::floor(time / 60);
    double timeSec = std::fmod(time, 1);
    if (timeHour >= 1)
        ui.lineEdit_time->setText(QString::number(timeHour) + " h "
            + QString::number(time - 60 * timeHour - timeSec) + " m "
            + QString::number(std::floor(60 * timeSec)) + " s");
    else if (time >= 1)
        ui.lineEdit_time->setText(QString::number(time - timeSec) + " m "
            + QString::number(std::floor(60 * timeSec)) + " s");
    else ui.lineEdit_time->setText(QString::number(std::floor(60 * timeSec)) + " s");
}

// Activate spell when button pressed
void GrimoireCalculator::_activateSpell(int spellCost)
{
    if (ui.spinBox_current->value() - spellCost >= 0)
    {
        ui.spinBox_current->setValue(ui.spinBox_current->value() - spellCost);
        _updateTime();
    }
    else _errorDisplay(QString::fromStdString("Not enough magic to cast the spell!"));
}

// Error Dialog display
void GrimoireCalculator::_errorDisplay(QString& errorMessage)
{
    QMessageBox::warning(this, "Error!", errorMessage);
}

// Slot: Calculate menu button pressed
void GrimoireCalculator::calculatePressed()
{
    _calculate();
}

// Slot: Max Current Magic menu button pressed
void GrimoireCalculator::maxCurrentMagicPressed()
{
    ui.spinBox_current->setValue(ui.spinBox_maximum->value());
    _updateTime();
}

// Slot: Help menu button pressed
void GrimoireCalculator::helpPressed()
{
    std::string helpMessage = "<b><u>Calculate:</u></b> Calculates time needed to replenish magic and costs for spells.<br>"
        "<b><u>Max Current Magic:</u></b> Sets current magic equal to maximum magic.<br><br>"
        "You can click on the spells to apply their cost to your current magic.<br><i>(Calculate will be applied first.)</i>";
    QMessageBox::about(this, "Help", QString::fromStdString(helpMessage));
}

// Slot: About menu button pressed
void GrimoireCalculator::aboutPressed()
{
    QMessageBox::about(this, "About", "Developped by <a href='https://github.com/Asers387'>Asers387</a>");
}

// Slot: Spell 1 button pressed
void GrimoireCalculator::spell1Pressed()
{
    if (_calculate())
        _activateSpell(ui.spinBox_cost1->value());
}

// Slot: Spell 2 button pressed
void GrimoireCalculator::spell2Pressed()
{
    if (_calculate())
        _activateSpell(ui.spinBox_cost2->value());
}

// Slot: Spell 3 button pressed
void GrimoireCalculator::spell3Pressed()
{
    if (_calculate())
        _activateSpell(ui.spinBox_cost3->value());
}

// Slot: Spell 4 button pressed
void GrimoireCalculator::spell4Pressed()
{
    if (_calculate())
        _activateSpell(ui.spinBox_cost4->value());
}

// Slot: Spell 5 button pressed
void GrimoireCalculator::spell5Pressed()
{
    if (_calculate())
        _activateSpell(ui.spinBox_cost5->value());
}

// Slot: Spell 6 button pressed
void GrimoireCalculator::spell6Pressed()
{
    if (_calculate())
        _activateSpell(ui.spinBox_cost6->value());
}

// Slot: Spell 7 button pressed
void GrimoireCalculator::spell7Pressed()
{
    if (_calculate())
        _activateSpell(ui.spinBox_cost7->value());
}

// Slot: Spell 8 button pressed
void GrimoireCalculator::spell8Pressed()
{
    if (_calculate())
        _activateSpell(ui.spinBox_cost8->value());
}

// Slot: Spell 9 button pressed
void GrimoireCalculator::spell9Pressed()
{
    if (_calculate())
        _activateSpell(ui.spinBox_cost9->value());
}
