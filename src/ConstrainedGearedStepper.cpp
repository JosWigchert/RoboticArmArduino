#include "ConstrainedGearedStepper.h"

ConstrainedGearedStepper::ConstrainedGearedStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true)
    : GearedStepper(interface, pin1, pin2, pin3, pin4, enable)
{
}

ConstrainedGearedStepper::ConstrainedGearedStepper(void (*forward)(), void (*backward)())
    : GearedStepper(forward, backward)
{
}

ConstrainedGearedStepper::~ConstrainedGearedStepper()
{
}

void ConstrainedGearedStepper::setLimit(float upper, float lower)
{
    upperLimit = upper;
    lowerLimit = lower;
}

void ConstrainedGearedStepper::setUpperLimit(float upper)
{
    upperLimit = upper;
}

void ConstrainedGearedStepper::setLowerLimit(float lower)
{
    lowerLimit = lower;
}

float ConstrainedGearedStepper::getUpperLimit() const
{
    return upperLimit;
}

float ConstrainedGearedStepper::getLowerLimit() const
{
    return lowerLimit;
}

void ConstrainedGearedStepper::rotate(float angle, AngleType type)
{
    float fullCircle = (type == Degrees) ? 360 : 2 * PI;
    int stepsFullCircle = gearSet->calculateSteps(STEPS_PER_REV * microStep);

    long currentPosition = this->currentPosition();
    float currentAngle = currentPosition == 0 ? 0 : ((float)currentPosition / (float)stepsFullCircle) * fullCircle;
    float toRotateAngle = currentAngle + angle;
    
    float constrainedAngle = max(min(toRotateAngle, upperLimit), lowerLimit);
    float rotateAngle = constrainedAngle - currentAngle;
    int steps = gearSet->calculateSteps(((STEPS_PER_REV * microStep) * (rotateAngle / fullCircle)));
    move(steps);
}