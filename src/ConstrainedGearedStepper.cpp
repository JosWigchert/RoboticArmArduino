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

void ConstrainedGearedStepper::setLimit(double upper, double lower)
{
    upperLimit = upper;
    lowerLimit = lower;
}

void ConstrainedGearedStepper::setUpperLimit(double upper)
{
    upperLimit = upper;
}

void ConstrainedGearedStepper::setLowerLimit(double lower)
{
    lowerLimit = lower;
}

double ConstrainedGearedStepper::getUpperLimit() const
{
    return upperLimit;
}

double ConstrainedGearedStepper::getLowerLimit() const
{
    return lowerLimit;
}

void ConstrainedGearedStepper::rotate(double angle, AngleType type)
{
    double fullCircle = (type == Degrees) ? 360 : 2 * PI;
    uint32_t stepsFullCircle = gearSet->calculateSteps(STEPS_PER_REV * microStep);

    long currentPosition = this->currentPosition();

    double currentAngle = currentPosition == 0 ? 0 : ((double)currentPosition / (double)stepsFullCircle) * fullCircle;
    double toRotateAngle = currentAngle + angle;

    double constrainedAngle = max(min(toRotateAngle, upperLimit), lowerLimit);
    double rotateAngle = constrainedAngle - currentAngle;

    uint32_t steps = round(gearSet->calculateSteps((STEPS_PER_REV * microStep)) * (rotateAngle / fullCircle));
    move(steps);
}