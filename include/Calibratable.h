#pragma once

#include <Bounce2.h>

#include "ICalibrateable.h"

class Calibratable : public ICalibratable
{
protected:
    Bounce *limitSwitch = nullptr;
public:
    Calibratable(/* args */);
    ~Calibratable();

    virtual void setLimitSwitch(uint8_t pin, uint8_t mode = INPUT_PULLUP) override;
    virtual void updateLimitSwitch() override;
};
