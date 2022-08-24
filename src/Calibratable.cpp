#include "Calibratable.h"

Calibratable::Calibratable(/* args */)
{
}

Calibratable::~Calibratable()
{
    if (limitSwitch != nullptr)
    {
        delete limitSwitch;
    }
}

void Calibratable::setLimitSwitch(uint8_t pin, uint8_t mode)
{
    limitSwitch = new Bounce();
    limitSwitch->attach(pin, mode);
    limitSwitch->interval(5);
}

void Calibratable::updateLimitSwitch()
{
    limitSwitch->update();
}
