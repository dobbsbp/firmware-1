#ifndef CONFIG_H
#define CONFIG_H

#define FWD_PIN A2              // VFD FWD Pin
#define REV_PIN A3              // VFD REV Pin

#define PROXIMITY_INPUT 7       // Proximity Sensor Pin (usually the black)
#define PROXIMITY_TIMEOUT 3000  // Max. delta time between the sensor's on/off. This is used to recognize a jamming 

#define RELAY_ON 0              // The relay bank's on value (eg: normally closed) 
#define RELAY_OFF 255           // The relay bank's off value (eg: normally closed) 

#define DIR_SWITCH_UP 3         // The 3 position's up output (digital in)
#define DIR_SWITCH_DOWN 4       // The 3 position's down output (digital in)

#define STARTING_TIMEOUT 2000   // Threshold, time needed to startup motor
#define REVERSING_TIMEOUT 2000  // Threshold, time needed to reverse motor
#define MAX_REVERSE_TRIALS 2    // Max. trials to reverse before aborting

#define DEBUG false

////////////////////////////////////////////////////////////////////////////////
//
//    Optional
//


// Temperature sensor
#define HAS_TEMPERTURE true

#define TEMPERTURE_SCK_PIN 10
#define TEMPERTURE_CS_PIN 9
#define TEMPERTURE_SO 8

#define TEMPERTURE_INTERVAL 1000   // Senor read interval, MAX6675 wants it over 1000
#define TEMPERTURE_MAX 40           // Max. motor temperature, in C

// Alarm sound
#define ALARM_SOUND TRUE
#define ALARM_SOUND_PIN 11

#endif
