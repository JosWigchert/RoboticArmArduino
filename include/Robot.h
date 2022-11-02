#pragma once

#include "ConstrainedGearedStepper.h"
#include "pins/pins.h"
#include "config/RobotConfig.h"
#include "Point3D.h"

class Robot
{
public:
    GearedStepper *baseStepper;
    ConstrainedGearedStepper *lowerArmStepper;
    ConstrainedGearedStepper *upperArmStepper;

protected:
    RobotConfig config;
    bool enabled;

    Point3D previousLocation;
    Point3D currentLocation;

public:
    void initialize(RobotConfig config);

    void moveTo(Point3D point);
    
    bool run();
    
    void enable();
    void disable();
    void reset();

protected:
    Point3D constrainPoint(Point3D point);
    Point3D mapPointOnCircle(Point3D point, Point3D center, float radius);
    void inverseKinetic(Point3D point, float &baseRotation, float &lowerArmRotation, float &upperArmRotation);
    float calculateTime(float distance, float maxSpeed, float maxAcceleration);
    float calculateAcceleration(float distance, float maxSpeed, float targetTime);
    void printStatus(char* name, float from, float to, float accel, float duration);

public:
    Robot(/* args */);
    ~Robot();
};

