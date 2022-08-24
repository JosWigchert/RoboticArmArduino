#pragma once

#include <Arduino.h>

struct JointConfig
{
    uint8_t    stepPin;
    uint8_t     dirPin;
    uint8_t  enablePin;
    float       length;
    float        speed;
    float acceleration;
    bool directionInverted = false;
    bool      stepInverted = false;
    bool    enableInverted = false;
};

struct BaseJointConfig : JointConfig
{
};

struct ArmJointConfig : JointConfig
{
    float lowerAngleLimit;
    float upperAngleLimit;
};

struct RobotConfig
{
    BaseJointConfig base;
    ArmJointConfig lowerArm;
    ArmJointConfig upperArm;

    float baseDeadspaceDiameter;
};