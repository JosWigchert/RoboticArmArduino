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
    baseStepper->setMaxSpeed(config.base.speed);
    baseStepper->setAcceleration(config.base.acceleration);
    baseStepper->setEnablePin(config.base.enablePin);


    lowerArmStepper = new ConstrainedGearedStepper(1, config.lowerArm.stepPin, config.lowerArm.dirPin);
    lowerArmStepper->setPinsInverted(config.lowerArm.directionInverted, config.lowerArm.stepInverted, config.lowerArm.enableInverted);
    lowerArmStepper->setGearRatio(20, 91);
    lowerArmStepper->setMicroStep(GearedStepper::MicroStep16);
    lowerArmStepper->setMaxSpeed(config.lowerArm.speed);
    lowerArmStepper->setAcceleration(config.lowerArm.acceleration);
    lowerArmStepper->setLimit(config.lowerArm.upperAngleLimit, config.lowerArm.lowerAngleLimit);
    lowerArmStepper->setEnablePin(config.lowerArm.enablePin);


    upperArmStepper = new ConstrainedGearedStepper(1, config.upperArm.stepPin, config.upperArm.dirPin);
    upperArmStepper->setPinsInverted(config.upperArm.directionInverted, config.upperArm.stepInverted, config.upperArm.enableInverted);
    upperArmStepper->setGearRatio(20, 91);
    upperArmStepper->setMicroStep(GearedStepper::MicroStep16);
    upperArmStepper->setMaxSpeed(config.upperArm.speed);
    upperArmStepper->setAcceleration(config.upperArm.acceleration);
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
    }

    float baseRotation;
    float lowerArmRotation;
    float upperArmRotation;

    Point3D actualPoint = constrainPoint(point);

    inverseKinetic(actualPoint, baseRotation, lowerArmRotation, upperArmRotation);

    baseStepper->rotateTo(baseRotation);
    lowerArmStepper->rotateTo(lowerArmRotation);
    upperArmStepper->rotateTo(upperArmRotation);
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

    Serial.print("Base rotation: ");
    Serial.println(baseRotation);

    Serial.print("Lower arm rotation: ");
    Serial.println(lowerArmRotation);

    Serial.print("Upper arm rotation: ");
    Serial.println(upperArmRotation);
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