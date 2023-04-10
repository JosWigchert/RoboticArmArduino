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

uint32_t GearedStepper::getStepsToMove(double angle, AngleType type)
{
    double fullCircle = (type == Degrees) ? 360 : 2 * PI;
    uint32_t steps = round(gearSet->calculateSteps(STEPS_PER_REV * microStep) * (angle / fullCircle));
    return steps;
}

void GearedStepper::moveGeared(uint32_t steps)
{
    move(gearSet->calculateSteps(steps * microStep));
}

void GearedStepper::moveToGeared(uint32_t steps)
{
    moveTo(gearSet->calculateSteps(steps * microStep));
}

void GearedStepper::rotate(double angle, AngleType type)
{
    Serial.print("Rotating: "); Serial.println(angle);

    long steps = getStepsToMove(angle);
    move(steps);
}

void GearedStepper::rotateTo(double angle, AngleType type)
{
    double fullCircle = (type == Degrees) ? 360 : 2 * PI;
    double normalizedAngle = fmod(angle, fullCircle);

    long currentPosition = this->currentPosition();
    double currentAngle = getCurrentRotation(type);
    
    rotate(normalizedAngle - currentAngle, type);
    // rotate shortest side
    // double currentNormalizedAngle = fmod(fullCircle + currentAngle, fullCircle);

    // double distanceCW = fmod(fullCircle + currentNormalizedAngle + normalizedAngle, fullCircle);
    // double distanceCCW = fmod(fullCircle + currentNormalizedAngle - normalizedAngle, fullCircle);

    // double distanceCW = currentAngle + normalizedAngle;
    // double distanceCCW = currentAngle - normalizedAngle;

    // rotate to

    // rotate(distanceCW < distanceCCW ? distanceCW : -distanceCCW, type);
}

double GearedStepper::getCurrentRotation(AngleType type)
{
    double fullCircle = (type == Degrees) ? 360 : 2 * PI;
    uint32_t stepsFullCircle = gearSet->calculateSteps(STEPS_PER_REV * microStep);

    long currentPosition = this->currentPosition();
    return currentPosition == 0 ? 0 : ((double)currentPosition / (double)stepsFullCircle) * fullCircle;
}

void GearedStepper::calibrate()
{

}