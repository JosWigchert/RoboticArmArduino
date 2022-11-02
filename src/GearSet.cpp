#include "GearSet.h"

GearSet::GearSet()
{
}

GearSet::GearSet(uint32_t driveTeeth, uint32_t drivenTeeth)
{
    driveGear = driveTeeth;
    drivenGear = driveTeeth;
}

GearSet::~GearSet()
{
}

uint32_t GearSet::getDriveGear()
{
    return driveGear;
}

void GearSet::setDriveGear(uint32_t teeth)
{
    driveGear = teeth;
}

uint32_t GearSet::getDrivenGear()
{
    return drivenGear;
}

void GearSet::setDrivenGear(uint32_t teeth)
{
    drivenGear = teeth;
}

void GearSet::setGearRatio(uint32_t driveTeeth, uint32_t drivenTeeth)
{
    driveGear = driveTeeth;
    drivenGear = drivenTeeth;
}

double GearSet::getGearRatio()
{
    return (double)drivenGear / (double)driveGear;
}

uint32_t  GearSet::calculateSteps(uint32_t steps)
{
    return steps * getGearRatio();
}