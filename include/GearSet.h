#pragma once

#include <Arduino.h>

class GearSet
{
public:
    uint32_t getDriveGear();
    void setDriveGear(uint32_t teeth);
    uint32_t getDrivenGear();
    void setDrivenGear(uint32_t teeth);

    void setGearRatio(uint32_t driveTeeth, uint32_t drivenTeeth);

    double getGearRatio();
    uint32_t calculateSteps(uint32_t steps);

private:
    uint32_t driveGear = 0;
    uint32_t drivenGear = 0;

public:
    GearSet();
    GearSet(uint32_t driveTeeth, uint32_t drivenTeeth);
    ~GearSet();
};

