#pragma once

#include "GearedStepper.h"

class ConstrainedGearedStepper : public GearedStepper
{
public:
    void setLimit(float upper, float lower);
    void setUpperLimit(float upper);
    void setLowerLimit(float lower);

    float getUpperLimit() const;
    float getLowerLimit() const;

    virtual void rotate(float angle, AngleType type = Degrees) override;
protected:
    float upperLimit;
    float lowerLimit;
public:
    ConstrainedGearedStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true);
    ConstrainedGearedStepper(void (*forward)(), void (*backward)());
    ~ConstrainedGearedStepper();

};
