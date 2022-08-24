#pragma once

#include <Arduino.h>

class ICalibratable {
public: 
    virtual void calibrate() = 0;
    virtual void setLimitSwitch(uint8_t pin, uint8_t mode = INPUT_PULLUP) = 0;
    virtual void updateLimitSwitch() = 0;
};