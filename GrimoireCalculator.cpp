#include "GrimoireCalculator.h"

GrimoireCalculator::GrimoireCalculator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    _readState();
}

/*
 * Validates current magic and calculates time and costs
 * If invalid, displays error message and returns false ; else returns true
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
    timeHour = std::floor(time / 60);
    timeSec = std::floor(60 * std::fmod(time, 1));
    timeMin = time - 60 * std::floor(time / 60) - std::fmod(time, 1);
    _updateTimeFormat();
}

// Format updated time until replenished
void GrimoireCalculator::_updateTimeFormat()
{
    if (timeHour >= 1)
        ui.lineEdit_time->setText(QString::number(timeHour) + " h "
            + QString::number(timeMin) + " m "
            + QString::number(timeSec) + " s");
    else if (timeMin >= 1)
        ui.lineEdit_time->setText(QString::number(timeMin) + " m "
            + QString::number(timeSec) + " s");
    else ui.lineEdit_time->setText(QString::number(timeSec) + " s");
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
    QMessageBox messageBox(QMessageBox::Warning, "Error!", errorMessage, QMessageBox::Ok, this);
    messageBox.exec();
}

/*
 * Reads state of app from the state file
 * Sets values into app
 */
void GrimoireCalculator::_readState()
{
    struct stat buf;
    if (stat("state", &buf) == 0) // Checks if file exists
    {
        std::ifstream stateFile("state");
        try
        {
            std::string line;
            getline(stateFile, line);
            int currentMagic = std::stoi(line);
            getline(stateFile, line);
            int maximumMagic = std::stoi(line);
            if (currentMagic < 0 || currentMagic > 999 || maximumMagic < 0 || maximumMagic > 999 || currentMagic > maximumMagic)
                throw std::logic_error("");
            ui.spinBox_current->setValue(currentMagic);
            ui.spinBox_maximum->setValue(maximumMagic);
        }
        catch (std::logic_error&)
        {
            _errorDisplay(QString::fromStdString("State file is invalid, resetting values..."));
        }
        stateFile.close();
    }
    else
    {
        std::ofstream stateFile("state");
        stateFile.close();
    }
    _calculate();
}

// Saves state of app to the state file
void GrimoireCalculator::_saveState()
{
    std::ofstream stateFile("state");
    stateFile << std::to_string(ui.spinBox_current->value()) << "\n"
        << std::to_string(ui.spinBox_maximum->value());
}

// Real-Time calculation of current magic and time until replenished
void GrimoireCalculator::_realTime()
{
    auto preciseTime = std::chrono::high_resolution_clock::now();
    while (true)
    {
        preciseTime += (std::chrono::seconds)1;
        std::this_thread::sleep_until(preciseTime);
        if (!realTimeActivated) break;

        if (!(timeHour == 0 && timeMin == 0 && timeSec == 0))
        {
            timeSec -= 1;
            if (timeSec == -1)
            {
                timeSec = 59;
                timeMin -= 1;
                if (timeMin == -1)
                {
                    timeMin = 59;
                    timeHour -= 1;
                }
            }
            _updateTimeFormat();
        }
    }
    realTimeThread.detach();
}

/*
 * Override of closeEvent function
 * Used to save state of app when closed
 */
void GrimoireCalculator::closeEvent(QCloseEvent* event)
{
    if (realTimeActivated) realTimeThread.detach();
    _saveState();
    event->accept();
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

// Slot: Real-Time menu button pressed
void GrimoireCalculator::realTimePressed()
{
    if (ui.realTimeAction->isChecked())
    {
        realTimeActivated = true;
        realTimeThread = std::thread(&GrimoireCalculator::_realTime, this);
    }
    else
    {
        realTimeActivated = false;
    }
}

// Slot: Help menu button pressed
void GrimoireCalculator::helpPressed()
{
    QString helpMessage = "Costs are indicated to the right of each spell.<br><br>"
        "<b><u>Calculate:</u></b> Calculates time needed to replenish magic and costs for spells.<br>"
        "<b><u>Max Current Magic:</u></b> Sets current magic equal to maximum magic.</b><br><br>"
        "You can click on the spells to apply their cost to your current magic.<br><i>(Calculate will be applied first.)</i>";
    QMessageBox messageBox(QMessageBox::NoIcon, "Help", helpMessage, QMessageBox::Ok, this);
    messageBox.exec();
}

// Slot: About menu button pressed
void GrimoireCalculator::aboutPressed()
{
    QString aboutMessage = "Version 2.0<br>"
        "Developped by <a href='https://github.com/Asers387'>Asers387</a>";
    QMessageBox messageBox(QMessageBox::NoIcon, "About", aboutMessage, QMessageBox::Ok, this);
    messageBox.exec();
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
