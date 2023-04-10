#ifdef CREALITY
#include "pins_creality.h"
#endif
#ifdef ANET
#include "pins_anet.h"
#endif


#define BASE_STEP_PIN                          Y_STEP_PIN
#define BASE_DIR_PIN                           Y_DIR_PIN
#define BASE_ENABLE_PIN                        Y_ENABLE_PIN

#define LOWER_ARM_STEP_PIN                     X_STEP_PIN
#define LOWER_ARM_DIR_PIN                      X_DIR_PIN
#define LOWER_ARM_ENABLE_PIN                   X_ENABLE_PIN

#define UPPER_ARM_STEP_PIN                     Z_STEP_PIN
#define UPPER_ARM_DIR_PIN                      Z_DIR_PIN
#define UPPER_ARM_ENABLE_PIN                   Z_ENABLE_PIN