//
// Limit Switches
//
#define X_STOP_PIN                            18
#define Y_STOP_PIN                            19
#define Z_STOP_PIN                            20

//
// Steppers
//
#define X_STEP_PIN                            15
#define X_DIR_PIN                             21

#define Y_STEP_PIN                            22
#define Y_DIR_PIN                             23

#define Z_STEP_PIN                             3
#define Z_DIR_PIN                              2

#define E0_STEP_PIN                            1
#define E0_DIR_PIN                             0

#define X_ENABLE_PIN                           14
#define Y_ENABLE_PIN                           14
#define Z_ENABLE_PIN                           26
#define E0_ENABLE_PIN                          14

//
// LCD
//
#define LCD_SDSS                              31  // Smart Controller SD card reader (rather than the Melzi)
#define LCD_PINS_RS                           28  // ST9720 CS
#define LCD_PINS_ENABLE                       17  // ST9720 DAT
#define LCD_PINS_D4                           30  // ST9720 CLK


/**
  PIN:   0   Port: B0        E0_DIR_PIN                  protected
  PIN:   1   Port: B1        E0_STEP_PIN                 protected
  PIN:   2   Port: B2        Z_DIR_PIN                   protected
  PIN:   3   Port: B3        Z_STEP_PIN                  protected
  PIN:   4   Port: B4        AVR_SS_PIN                  protected
  .                          FAN_PIN                     protected
  .                       SD_SS_PIN                      protected
  PIN:   5   Port: B5        AVR_MOSI_PIN                Output = 1
  .                       SD_MOSI_PIN                    Output = 1
  PIN:   6   Port: B6        AVR_MISO_PIN                Input  = 0    TIMER3A   PWM:     0    WGM: 1    COM3A: 0    CS: 3    TCCR3A: 1    TCCR3B: 3    TIMSK3: 0
  .                       SD_MISO_PIN                    Input  = 0
  PIN:   7   Port: B7        AVR_SCK_PIN                 Output = 0    TIMER3B   PWM:     0    WGM: 1    COM3B: 0    CS: 3    TCCR3A: 1    TCCR3B: 3    TIMSK3: 0
  .                       SD_SCK_PIN                     Output = 0
  PIN:   8   Port: D0        RXD                         Input  = 1
  PIN:   9   Port: D1        TXD                         Input  = 0
  PIN:  10   Port: D2        BTN_EN2                     Input  = 1
  PIN:  11   Port: D3        BTN_EN1                     Input  = 1
  PIN:  12   Port: D4        HEATER_BED_PIN              protected
  PIN:  13   Port: D5        HEATER_0_PIN                protected
  PIN:  14   Port: D6        E0_ENABLE_PIN               protected
  .                          X_ENABLE_PIN                protected
  .                          Y_ENABLE_PIN                protected
  PIN:  15   Port: D7        X_STEP_PIN                  protected
  PIN:  16   Port: C0        BTN_ENC                     Input  = 1
  .                          SCL                         Input  = 1
  PIN:  17   Port: C1        LCD_PINS_ENABLE             Output = 0
  .                          SDA                         Output = 0
  PIN:  18   Port: C2        X_MIN_PIN                   protected
  .                          X_STOP_PIN                  protected
  PIN:  19   Port: C3        Y_MIN_PIN                   protected
  .                          Y_STOP_PIN                  protected
  PIN:  20   Port: C4        Z_MIN_PIN                   protected
  .                          Z_STOP_PIN                  protected
  PIN:  21   Port: C5        X_DIR_PIN                   protected
  PIN:  22   Port: C6        Y_STEP_PIN                  protected
  PIN:  23   Port: C7        Y_DIR_PIN                   protected
  PIN:  24   Port: A7        TEMP_0_PIN                  protected
  PIN:  25   Port: A6        TEMP_BED_PIN                protected
  PIN:  26   Port: A5        Z_ENABLE_PIN                protected
  PIN:  27   Port: A4        BEEPER_PIN                  Output = 0
  PIN:  28   Port: A3        LCD_PINS_RS                 Output = 0
  PIN:  29   Port: A2        <unused/unknown>            Input  = 0
  PIN:  30   Port: A1        LCD_PINS_D4                 Output = 1
  PIN:  31   Port: A0        SDSS                        Output = 1
*/

/**
 *    EXP1 Connector                      EXP1 as CR10 STOCKDISPLAY
 *        ------                                      ------
 *   PA4 | 1  2 | PC0                     BEEPER_PIN | 1  2 | BTN_ENC
 *   PD3 | 3  4 | RESET                      BTN_EN1 | 3  4 | RESET
 *   PD2   5  6 | PA1                        BTN_EN2   5  6 | LCD_PINS_D4     (ST9720 CLK)
 *   PA3 | 7  8 | PC1        (ST9720 CS) LCD_PINS_RS | 7  8 | LCD_PINS_ENABLE (ST9720 DAT)
 *   GND | 9 10 | 5V                             GND | 9 10 | 5V
 *        ------                                      ------
 */
