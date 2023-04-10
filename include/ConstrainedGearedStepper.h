#pragma once

#include "GearedStepper.h"

class ConstrainedGearedStepper : public GearedStepper
{
public:
    void setLimit(double upper, double lower);
    void setUpperLimit(double upper);
    void setLowerLimit(double lower);

    double getUpperLimit() const;
    double getLowerLimit() const;

    virtual void rotate(double angle, AngleType type = Degrees) override;
protected:
    double upperLimit;
    double lowerLimit;
public:
    ConstrainedGearedStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true);
    ConstrainedGearedStepper(void (*forward)(), void (*backward)());
    ~ConstrainedGearedStepper();

};
