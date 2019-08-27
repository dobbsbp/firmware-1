#ifndef CONFIG_H
#define CONFIG_H

#define FWD_PIN A2              // VFD FWD Pin
#define REV_PIN A3              // VFD REV Pin

#define RELAY_ON 0              // The relay bank's on value (eg: normally closed) 
#define RELAY_OFF 255           // The relay bank's off value (eg: normally closed) 

#define DIR_SWITCH_UP 3         // The 3 position's up output (digital in)
#define DIR_SWITCH_DOWN 4       // The 3 position's down output (digital in)

#define STARTING_TIMEOUT 2000   // Threshold, time needed to startup motor
#define REVERSING_TIMEOUT 2000  // Threshold, time needed to reverse motor
#define MAX_REVERSE_TRIALS 2    // Max. trials to reverse before aborting

#define DEBUG false
#define DEBUG_INTERVAL 2000

////////////////////////////////////////////////////////////////////////////////
//
//    Optional : you need to activate at least one sensor, HALL or/and PROXIMITY
//

// Proximity sensor - uncomment to activate
#define HAS_PROXIMITY
#define PROXIMITY_INPUT 7       // Proximity Sensor Pin (usually the black)
#define PROXIMITY_TIMEOUT 3000  // Max. delta time between the sensor's on/off. This is used to recognize a jamming.


// Temperature sensor - uncomment to activate
// #define HAS_TEMPERTURE
#define TEMPERTURE_SCK_PIN 10
#define TEMPERTURE_CS_PIN 9
#define TEMPERTURE_SO 8

#define TEMPERTURE_INTERVAL 1000    // Senor read interval, MAX6675 wants it over 1000
#define TEMPERTURE_MAX 60           // Max. motor temperature, in C

// Alarm sound - uncomment to activate
// #define ALARM_SOUND
#define ALARM_SOUND_PIN 11


// Hall Sensor (Experimental)- uncomment to activate
// #define HAS_HALL
#define HALL_INTERVAL 500           // hall sensor read interval
#define HALL_PIN A0                 // this pin has a hall sensor connected to it that measures the output current to the motor
#define MAX_AMPS 650                // this is the value over which the hall sensor signal will register as a jam


#endif
