#ifndef CONFIG_H
#define CONFIG_H

#define FWD_PIN A5                          // VFD FWD Pin. This goes into the relay.
#define REV_PIN A4                          // VFD REV Pin. This goes into the relay.

#define RELAY_ON 0                          // The relay bank's on value (eg: normally closed) 
#define RELAY_OFF 255                       // The relay bank's off value (eg: normally closed) 

#define DIR_SWITCH_UP_PIN 1                 // The 3 position's up output
#define DIR_SWITCH_DOWN_PIN 2               // The 3 position's down output

#define STARTING_TIMEOUT 2000               // Threshold, time needed to startup motor
#define REVERSING_TIMEOUT 2000              // Threshold, time needed to reverse motor
#define MAX_REVERSE_TRIALS 2                // Max. trials to reverse before aborting (goes in FATAL state, unlock via 3pos switch = 0 or reset button)

#define DEBUG true
#define DEBUG_INTERVAL 2000

#define HAS_AUTO_REVERSE true               // Set true to enable auto-reverse, false to wire the 3-pos switch directly to the VFD FWD/REV inputs. 
#define ENABLE_AUTO_REVERSE_PIN 8           // The pin to disable/enable auto-reverse - Not impl.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Optional : you need to activate at least one sensor, HALL or/and IR and/or PROXIMITY
//

// Proximity sensor - uncomment to activate
// #define HAS_PROXIMITY
#define PROXIMITY_PIN 9                     // Proximity Sensor Pin (usually the black)
#define PROXIMITY_TIMEOUT 3000              // Max. delta time between the sensor's on/off. This is used to recognize a jamming.

// IR sensor ( LM393 ) - not. impl. - experimental - uncomment to activate
// #define HAS_IR
#define IR_PIN 2                            // Arduino has fixed pins for using interrupts, don't change this 
#define IR_INTERVAL 1000                    // re-compute values in this interval


// Reset button - uncomment to activate. This will unlock the fatal state in case of jamming or other problems.
#define HAS_RESET
#define RESET_PIN 3

// Status LEDS (ok, error) - uncomment to activate
#define HAS_STATUS
#define STATUS_OK_PIN A3                    // This goes into the relay
#define STATUS_ERROR_PIN A2                 // This goes into the relay

// Some VFDs have an error signal. Consume this to set FATAL state - Not impl.  - uncomment to activate
#define VFD_ERROR_PIN 13
// VFDs have an reset signal. Consume this in case we have a reset button - Not impl.  - uncomment to activate
#define VFD_RESET_PIN 12

// Motor temperature sensor - uncomment to activate. If the TEMPERTURE_MAX has been exceeded, it will stop the motor and goes into fatal mode. 
#define HAS_TEMPERTURE
#define TEMPERTURE_SCK_PIN 5
#define TEMPERTURE_CS_PIN 6
#define TEMPERTURE_SO_PIN 7

#define TEMPERTURE_INTERVAL 1000            // Senor read interval, MAX6675 wants it over 1000
#define TEMPERTURE_MAX 50                   // Max. motor temperature, in C

// Alarm sound - uncomment to activate
// #define ALARM_SOUND
#define ALARM_SOUND_PIN 11


// Hall Sensor (Experimental)- uncomment to activate
// #define HAS_HALL
#define HALL_INTERVAL 500                 // hall sensor read interval
#define HALL_PIN A0                       // this pin has a hall sensor connected to it that measures the output current to the motor
#define MAX_AMPS 650                      // this is the value over which the hall sensor signal will register as a jam

#endif
