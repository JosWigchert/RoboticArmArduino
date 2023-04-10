#include "Robot.h"

Robot::Robot(/* args */)
{
}

Robot::~Robot()
{
    if (baseStepper != nullptr)
        delete baseStepper;
    if (lowerArmStepper != nullptr)
        delete lowerArmStepper;
    if (upperArmStepper != nullptr)
        delete upperArmStepper;
}

void Robot::initialize(RobotConfig config)
{
    this->config = config;

    baseStepper = new GearedStepper(1, config.base.stepPin, config.base.dirPin);
    baseStepper->setPinsInverted(config.base.directionInverted, config.base.stepInverted, config.base.enableInverted);
    baseStepper->setGearRatio(20, 91);
    baseStepper->setMicroStep(GearedStepper::MicroStep16);
    baseStepper->setMaxSpeed(config.base.maxSpeed);
    baseStepper->setAcceleration(config.base.maxAcceleration);
    baseStepper->setEnablePin(config.base.enablePin);


    lowerArmStepper = new ConstrainedGearedStepper(1, config.lowerArm.stepPin, config.lowerArm.dirPin);
    lowerArmStepper->setPinsInverted(config.lowerArm.directionInverted, config.lowerArm.stepInverted, config.lowerArm.enableInverted);
    lowerArmStepper->setGearRatio(1*30, 15*45);
    lowerArmStepper->setMicroStep(GearedStepper::MicroStep16);
    lowerArmStepper->setMaxSpeed(config.lowerArm.maxSpeed);
    lowerArmStepper->setAcceleration(config.lowerArm.maxAcceleration);
    lowerArmStepper->setLimit(config.lowerArm.upperAngleLimit, config.lowerArm.lowerAngleLimit);
    lowerArmStepper->setEnablePin(config.lowerArm.enablePin);


    upperArmStepper = new ConstrainedGearedStepper(1, config.upperArm.stepPin, config.upperArm.dirPin);
    upperArmStepper->setPinsInverted(config.upperArm.directionInverted, config.upperArm.stepInverted, config.upperArm.enableInverted);
    upperArmStepper->setGearRatio(20, 91);
    upperArmStepper->setMicroStep(GearedStepper::MicroStep16);
    upperArmStepper->setMaxSpeed(config.upperArm.maxSpeed);
    upperArmStepper->setAcceleration(config.upperArm.maxAcceleration);
    upperArmStepper->setLimit(config.upperArm.upperAngleLimit, config.upperArm.lowerAngleLimit);
    upperArmStepper->setEnablePin(config.upperArm.enablePin);

    disable();
}

bool Robot::run()
{
    bool output = baseStepper->run();
    output = lowerArmStepper->run() | output; 
    output = upperArmStepper->run() | output; 
    return output;
}

void Robot::moveTo(Point3D point)
{
    if (!enabled)
    {
        Serial.println("Motors are not enabled!");
        Serial.println("Stopping job");
        return;
    }

    float baseRotation;
    float lowerArmRotation;
    float upperArmRotation;

    previousLocation = currentLocation;
    currentLocation = constrainPoint(point);

    inverseKinetic(currentLocation, baseRotation, lowerArmRotation, upperArmRotation);

    float currentbaseRotation     = baseStepper->getCurrentRotation();
    float currentlowerArmRotation = lowerArmStepper->getCurrentRotation();
    float currentupperArmRotation = upperArmStepper->getCurrentRotation();

    float     baseRotationSteps = baseStepper->getStepsToMove(abs(currentbaseRotation - baseRotation));
    float lowerArmRotationSteps = lowerArmStepper->getStepsToMove(abs(currentlowerArmRotation - lowerArmRotation));
    float upperArmRotationSteps = upperArmStepper->getStepsToMove(abs(currentupperArmRotation - upperArmRotation));

    float baseDuration = calculateTime(baseRotationSteps, config.base.maxSpeed, config.base.maxAcceleration);
    float lowerArmDuration = calculateTime(lowerArmRotationSteps, config.lowerArm.maxSpeed, config.lowerArm.maxAcceleration);
    float upperArmDuration = calculateTime(upperArmRotationSteps, config.upperArm.maxSpeed, config.upperArm.maxAcceleration);

    float maxDuration = max(baseDuration, max(lowerArmDuration, upperArmDuration));

    float baseAcceleration = calculateAcceleration(baseRotationSteps, config.base.maxSpeed, maxDuration);
    float lowerArmAcceleration = calculateAcceleration(lowerArmRotationSteps, config.lowerArm.maxSpeed, maxDuration);
    float upperArmAcceleration = calculateAcceleration(upperArmRotationSteps, config.upperArm.maxSpeed, maxDuration);

    baseDuration = calculateTime(baseRotationSteps, config.base.maxSpeed, baseAcceleration);
    lowerArmDuration = calculateTime(lowerArmRotationSteps, config.lowerArm.maxSpeed, lowerArmAcceleration);
    upperArmDuration = calculateTime(upperArmRotationSteps, config.upperArm.maxSpeed, upperArmAcceleration);

    printStatus("base", currentbaseRotation, baseRotation, baseAcceleration, baseDuration);
    printStatus("lowerArm", currentlowerArmRotation, lowerArmRotation, lowerArmAcceleration, lowerArmDuration);
    printStatus("upperArm", currentupperArmRotation, upperArmRotation, upperArmAcceleration, upperArmDuration);

    baseStepper->setAcceleration(baseAcceleration);
    lowerArmStepper->setAcceleration(lowerArmAcceleration);
    upperArmStepper->setAcceleration(upperArmAcceleration);

    baseStepper->rotateTo(baseRotation);
    lowerArmStepper->rotateTo(lowerArmRotation);
    upperArmStepper->rotateTo(upperArmRotation);
}

void Robot::printStatus(char* name, float from, float to, float accel, float duration)
{
    Serial.print("Rotationg ");
    Serial.print(name);
    Serial.print(" from ");
    Serial.print(from);
    Serial.print(" to ");
    Serial.print(to);
    Serial.print(" with acceleration ");
    Serial.print(accel);
    Serial.print(", which takes ");
    Serial.println(duration);
}

Point3D Robot::constrainPoint(Point3D point)
{
    Point3D center;
    center.x = 0; 
    center.y = 0; 
    center.z = config.base.length;
    float distance = point.distance(center);
    
    if (distance > (config.lowerArm.length + config.upperArm.length))
    {
        return mapPointOnCircle(point, center, config.lowerArm.length + config.upperArm.length);
    }
    else if (distance < config.baseDeadspaceDiameter)
    {
        return mapPointOnCircle(point, center, config.baseDeadspaceDiameter);
    }
    return point;
}

Point3D Robot::mapPointOnCircle(Point3D point, Point3D center, float diameter)
{
    Point3D toScale = point - center;
    toScale = toScale / toScale.length();
    toScale = toScale * diameter;
    return toScale;
}


void Robot::inverseKinetic(Point3D point, float &baseRotation, float &lowerArmRotation, float &upperArmRotation)
{
    float a1 = config.base.length;
    float a2 = config.lowerArm.length;
    float a3 = config.upperArm.length;

    float r1 = sqrt(pow(point.x, 2) + pow(point.y, 2));
    float r2 = point.z - a1;
    float r3 = sqrt(pow(r1, 2) + pow(r2, 2));

    float phi1 = acos((pow(a3, 2) - pow(a2, 2) - pow(r3, 2)) / (-2 * a2 * r3));
    float phi2 = atan2(r2, r1);
    float phi3 = acos((pow(r3, 2) - pow(a2, 2) - pow(a3, 2)) / (-2 * a2 * a3));

    float rho1 = atan2(point.y, point.x);
    float rho2 = phi1 + phi2;
    float rho3 = PI - phi3;

    baseRotation     = rho1 * 180 / PI;
    lowerArmRotation = rho2 * 180 / PI;
    upperArmRotation = rho3 * 180 / PI;
}

float Robot::calculateTime(float distance, float maxSpeed, float maxAcceleration)
{
    float timeToFullSpeed =  maxSpeed / maxAcceleration;
    double distanceTraveledToFullSpeed = .5f * maxAcceleration * (timeToFullSpeed * timeToFullSpeed);
    float time = (float)sqrt((distance / 2) / (.5f * maxAcceleration)) * 2;
    time += (distance / 2) <= distanceTraveledToFullSpeed ? 0 : (((distance / 2) - distanceTraveledToFullSpeed) / maxSpeed) * 2;

    return time;
}

float Robot::calculateAcceleration(float distance, float maxSpeed, float targetTime)
{
    float d = distance * 2;
    float alpha = d / (.5f * targetTime * targetTime);
    return alpha;
}

void Robot::enable()
{
    enabled = true;

    if (baseStepper != nullptr)
        baseStepper->enableOutputs();
    if (lowerArmStepper != nullptr)
        lowerArmStepper->enableOutputs();
    if (upperArmStepper != nullptr)
        upperArmStepper->enableOutputs();
}

void Robot::disable()
{
    enabled = false;

    if (baseStepper != nullptr)
        baseStepper->disableOutputs();
    if (lowerArmStepper != nullptr)
        lowerArmStepper->disableOutputs();
    if (upperArmStepper != nullptr)
        upperArmStepper->disableOutputs();
}

void Robot::reset()
{
    baseStepper->setCurrentPosition(0);
    lowerArmStepper->setCurrentPosition(0);
    upperArmStepper->setCurrentPosition(0);
}