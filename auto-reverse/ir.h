#ifndef IR_H
#define IR_H

/*/
	@link : http://androminarobot-english.blogspot.com/2017/03/encoder-and-arduinotutorial-about-ir.html
*/


unsigned int rpm = 0;									// RPM
float velocity = 0;										// Speed [Km/h]
volatile byte pulses = 0;								// Pulses per secs
unsigned long timeold = 0;
unsigned int pulsesperturn = 20;						// Number of notches the encoder disc has
const int wheel_diameter = 64;						// diameter [mm]
static volatile unsigned long debounce = 0;		//

void ir_count() {
	if (digitalRead(IR_PIN) && (micros() - debounce > 500) && digitalRead(IR_PIN)) {
		// Check again that the encoder sends a good signal and then check that the time is greater than 1000 microseconds and check again that the signal is correct.
		debounce = micros(); // Store the time to verify that we do not count the rebound in the signal.
		pulses++;
	}
}

void ir_setup() {
	pinMode(IR_PIN, INPUT);
	attachInterrupt(0, ir_count, RISING); // Configuration of interrupt 0, where it is connected. 
	pulses = 0;
	rpm = 0;
	timeold = 0;
}

void ir_loop() {
	if (millis() - timeold >= IR_INTERVAL) {
		noInterrupts(); // Don't process interrupts during calculations // We disconnect the interrupt so it doesn't act in this part of the program.
		rpm = (60 * 1000 / pulsesperturn) / (millis() - timeold) * pulses; // Calculate the revolutions per minute
		velocity = rpm * 3.1416 * wheel_diameter * 60 / 1000000; // Speed ​​calculation in [Km / h] 
		timeold = millis(); // We store the current time.
		pulses = 0; // Initialize the pulses.
		interrupts(); // Restart the interrupt processing // Reiniciamos la interrupción
	}
}


#endif

