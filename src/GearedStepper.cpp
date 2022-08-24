#include "GearedStepper.h"

GearedStepper::GearedStepper(uint8_t interface, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, bool enable)
    : AccelStepper(interface, pin1, pin2, pin3, pin4, enable)
{
    microStep = MicroStep16;
}

GearedStepper::GearedStepper(void (*forward)(), void (*backward)())
    : AccelStepper(forward, backward)
{
    microStep = MicroStep16;
}

GearedStepper::~GearedStepper()
{
    if (gearSet == nullptr)
    {
        delete gearSet;
    }
}

GearedStepper::MicroStep GearedStepper::getMicroStep()
{
    return microStep;
}

void GearedStepper::setMicroStep(MicroStep microStep)
{
    this->microStep = microStep;
}

void GearedStepper::setGearRatio(uint32_t driveTeeth, uint32_t drivenTeeth)
{
    gearSet->setGearRatio(driveTeeth, drivenTeeth);
}

void GearedStepper::moveGeared(long steps)
{
    move(gearSet->calculateSteps(steps * microStep));
}

void GearedStepper::moveToGeared(long steps)
{
    moveTo(gearSet->calculateSteps(steps * microStep));
}

void GearedStepper::rotate(float angle, AngleType type)
{
    float fullCircle = (type == Degrees) ? 360 : 2 * PI;
    int steps = gearSet->calculateSteps(((STEPS_PER_REV * microStep) * (angle / fullCircle)));
    move(steps);
}

void GearedStepper::rotateTo(float angle, AngleType type)
{
    float fullCircle = (type == Degrees) ? 360 : 2 * PI;
    float normalizedAngle = fmod(angle, fullCircle);
    int stepsFullCircle = gearSet->calculateSteps(STEPS_PER_REV * microStep);

    long currentPosition = this->currentPosition();
    float currentAngle = currentPosition == 0 ? 0 : ((float)currentPosition / (float)stepsFullCircle) * fullCircle;

    rotate(normalizedAngle - currentAngle, type);
    // rotate shortest side
    // float currentNormalizedAngle = fmod(fullCircle + currentAngle, fullCircle);

    // float distanceCW = fmod(fullCircle + currentNormalizedAngle + normalizedAngle, fullCircle);
    // float distanceCCW = fmod(fullCircle + currentNormalizedAngle - normalizedAngle, fullCircle);

    // float distanceCW = currentAngle + normalizedAngle;
    // float distanceCCW = currentAngle - normalizedAngle;

    // rotate to

    // rotate(distanceCW < distanceCCW ? distanceCW : -distanceCCW, type);
}

void GearedStepper::calibrate()
{

}