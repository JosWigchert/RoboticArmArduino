#include <Arduino.h>
#include <Bounce2.h>

// Define ANET or CREALIY for the correct pinout
#define ANET

#include "pins/pins.h"
#include "Split.h"
#include "ConstrainedGearedStepper.h"
#include "config/RobotConfig.h"
#include "Robot.h"

#define BASE_HEIGHT 11.0
#define BASE_DEADSPACE_DIAMETER 15.0

#define LOWER_ARM_LENGTH 30.0
#define LOWER_ARM_LOWER_ANGLE_LIMIT 0.0
#define LOWER_ARM_UPPER_ANGLE_LIMIT 90.0

#define UPPER_ARM_LENGTH 25.0
#define UPPER_ARM_LOWER_ANGLE_LIMIT -150.0
#define UPPER_ARM_UPPER_ANGLE_LIMIT 150.0

RobotConfig robotConfig;
Robot *robot;


FILE f_out;
int sput(char c, __attribute__((unused)) FILE* f) {return !Serial.write(c);}

void setup()
{
    Serial.begin(115200);
    Serial.setTimeout(10);

    fdev_setup_stream(&f_out, sput, nullptr, _FDEV_SETUP_WRITE); // cf https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gaf41f158c022cbb6203ccd87d27301226
    stdout = &f_out;

    Serial.println("Starting robot...");

    robotConfig.baseDeadspaceDiameter = BASE_DEADSPACE_DIAMETER;

    robotConfig.base.stepPin = BASE_STEP_PIN;
    robotConfig.base.dirPin = BASE_DIR_PIN;
    robotConfig.base.enablePin = BASE_ENABLE_PIN;
    robotConfig.base.length = BASE_HEIGHT;
    robotConfig.base.maxSpeed = 8000.0f;
    robotConfig.base.maxAcceleration = 3000.0f;
    robotConfig.base.enableInverted = true;

    robotConfig.lowerArm.stepPin = LOWER_ARM_STEP_PIN;
    robotConfig.lowerArm.dirPin = LOWER_ARM_DIR_PIN;
    robotConfig.lowerArm.enablePin = LOWER_ARM_ENABLE_PIN;
    robotConfig.lowerArm.length = LOWER_ARM_LENGTH;
    robotConfig.lowerArm.lowerAngleLimit = LOWER_ARM_LOWER_ANGLE_LIMIT;
    robotConfig.lowerArm.upperAngleLimit = LOWER_ARM_UPPER_ANGLE_LIMIT;
    robotConfig.lowerArm.maxSpeed = 8000.0f;
    robotConfig.lowerArm.maxAcceleration = 2000.0f;
    robotConfig.lowerArm.enableInverted = true;
    robotConfig.upperArm.directionInverted = true;

    robotConfig.upperArm.stepPin = UPPER_ARM_STEP_PIN;
    robotConfig.upperArm.dirPin = UPPER_ARM_DIR_PIN;
    robotConfig.upperArm.enablePin = UPPER_ARM_ENABLE_PIN;
    robotConfig.upperArm.length = UPPER_ARM_LENGTH;
    robotConfig.upperArm.lowerAngleLimit = UPPER_ARM_LOWER_ANGLE_LIMIT;
    robotConfig.upperArm.upperAngleLimit = UPPER_ARM_UPPER_ANGLE_LIMIT;
    robotConfig.upperArm.maxSpeed = 3000.0f;
    robotConfig.upperArm.maxAcceleration = 2000.0f;
    robotConfig.upperArm.enableInverted = true;
    robotConfig.upperArm.directionInverted = true;

    robot = new Robot();
    robot->initialize(robotConfig);
}

void handleInput(String command) 
{
    const int size = 20;
    int count = 0;
    String split[size];

    Split::split(command, ' ', split, size, count);

    if (count < 1) 
    {
        Serial.println("Not enough arguments"); 
        return;
    }

    if (split[0].charAt(0) == 'e')
    {
        Serial.println("Enable Motors"); 
        robot->enable();
    }
    else if (split[0].charAt(0) == 'd')
    {
        Serial.println("Disable Motors"); 
        robot->disable();
    }
    else if (split[0].charAt(0) == 'c')
    {
        Serial.println("Calibrating Robot"); 
        robot->reset();
    }
    else if (split[0] == "r")
    {
        if (count < 3)
        {
            Serial.println("Not enough arguments, need atleast 2"); 
            return;
        } 

        if (split[1] == "x")
        {
            int amount = split[2].toInt();
            Serial.print("Rotating lower arm: "); Serial.print(amount); Serial.println(" Degrees");
            robot->lowerArmStepper->rotateTo(amount);
        }
        else if (split[1] == "y")
        {
            int amount = split[2].toInt();
            Serial.print("Rotating base: "); Serial.print(amount); Serial.println(" Degrees");
            robot->baseStepper->rotateTo(amount);
        }
        else if (split[1] == "z")
        {
            int amount = split[2].toInt();
            Serial.print("Rotating upper arm: "); Serial.print(amount); Serial.println(" Degrees");
            robot->upperArmStepper->rotateTo(amount);
        }
    }
    else if (split[0] == "p")
    {
        if (count < 3)
        {
            Serial.println("Not enough arguments, need atleast 3"); 
            return;
        } 

        Point3D point;
        point.x = split[1].toFloat();
        point.y = split[2].toFloat();
        point.z = split[3].toFloat();

        Serial.println(point);

        robot->moveTo(point);
    }
}

void loop()
{
    if (Serial.available())
    {
        String command = Serial.readStringUntil('\r');
        handleInput(command);
    }

    robot->run();    
}

