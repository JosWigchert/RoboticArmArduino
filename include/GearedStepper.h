#pragma once

#include <AccelStepper.h>

#include "GearSet.h"
#include "Calibratable.h"

class GearedStepper : public AccelStepper, public Calibratable 
{
public:
    enum MicroStep { MicroStep1 = 1, MicroStep2 = 2, MicroStep4 = 4, MicroStep8 = 8, MicroStep16 = 16, MicroStep32 = 32 };
    enum AngleType { Degrees, Radians };
    const uint32_t STEPS_PER_REV = 200;
    
    MicroStep getMicroStep();
    void setMicroStep(MicroStep microStep);

    void setGearRatio(uint32_t driveTeeth, uint32_t drivenTeeth);

    uint32_t getStepsToMove(double angle, AngleType type = Degrees);

    void moveGeared(uint32_t steps);
    void moveToGeared(uint32_t steps);

    virtual void rotate(double angle, AngleType type = Degrees);
    virtual void rotateTo(double angle, AngleType type = Degrees);
    virtual double getCurrentRotation(AngleType type = Degrees);

    virtual void calibrate() override;

protected:
    MicroStep microStep = MicroStep1;
    GearSet *gearSet = new GearSet(1, 1);


public:
    /// Constructor. You can have multiple simultaneous steppers, all moving
    /// at different speeds and accelerations, provided you call their run()
    /// functions at frequent enough intervals. Current Position is set to 0, target
    /// position is set to 0. MaxSpeed and Acceleration default to 1.0.
    /// The motor pins will be initialised to OUTPUT mode during the
    /// constructor by a call to enableOutputs().
    /// \param[in] interface Number of pins to interface to. Integer values are
    /// supported, but it is preferred to use the \ref MotorInterfaceType symbolic names. 
    /// AccelStepper::DRIVER (1) means a stepper driver (with Step and Direction pins).
    /// If an enable line is also needed, call setEnablePin() after construction.
    /// You may also invert the pins using setPinsInverted().
    /// Caution: DRIVER implements a blocking delay of minPulseWidth microseconds (default 1us) for each step.
    /// You can change this with setMinPulseWidth().
    /// AccelStepper::FULL2WIRE (2) means a 2 wire stepper (2 pins required). 
    /// AccelStepper::FULL3WIRE (3) means a 3 wire stepper, such as HDD spindle (3 pins required). 
    /// AccelStepper::FULL4WIRE (4) means a 4 wire stepper (4 pins required). 
    /// AccelStepper::HALF3WIRE (6) means a 3 wire half stepper, such as HDD spindle (3 pins required)
    /// AccelStepper::HALF4WIRE (8) means a 4 wire half stepper (4 pins required)
    /// Defaults to AccelStepper::FULL4WIRE (4) pins.
    /// \param[in] pin1 Arduino digital pin number for motor pin 1. Defaults
    /// to pin 2. For a AccelStepper::DRIVER (interface==1), 
    /// this is the Step input to the driver. Low to high transition means to step)
    /// \param[in] pin2 Arduino digital pin number for motor pin 2. Defaults
    /// to pin 3. For a AccelStepper::DRIVER (interface==1), 
    /// this is the Direction input the driver. High means forward.
    /// \param[in] pin3 Arduino digital pin number for motor pin 3. Defaults
    /// to pin 4.
    /// \param[in] pin4 Arduino digital pin number for motor pin 4. Defaults
    /// to pin 5.
    /// \param[in] enable If this is true (the default), enableOutputs() will be called to enable
    /// the output pins at construction time.
    GearedStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true);
    /// Alternate Constructor which will call your own functions for forward and backward steps. 
    /// You can have multiple simultaneous steppers, all moving
    /// at different speeds and accelerations, provided you call their run()
    /// functions at frequent enough intervals. Current Position is set to 0, target
    /// position is set to 0. MaxSpeed and Acceleration default to 1.0.
    /// Any motor initialization should happen before hand, no pins are used or initialized.
    /// \param[in] forward void-returning procedure that will make a forward step
    /// \param[in] backward void-returning procedure that will make a backward step
    GearedStepper(void (*forward)(), void (*backward)());
    ~GearedStepper();
};


