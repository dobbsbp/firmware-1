#ifndef AUTO_REVERSE_H
#define AUTO_REVERSE_H

#include "features.h"

#ifdef HAS_RESET
	void resetSys() { stop(); }
#endif

void onFatal() {
	#ifdef ALARM_SOUND
		alarm();
	#endif

	#ifdef HAS_STATUS
		setStatus(true);
	#endif
}

// our main 'is shredding function', utilizing different sensors
bool isShredding() {
	bool ret = true;

	#ifdef HAS_PROXIMITY
	if (!proximityOk()) {
		return false;
	}
	#endif

	#ifdef HAS_HALL
		ret = hallOk();
	#endif

	return ret;
}

void auto_reverse_setup() {

}

void auto_reverse_loop() {
	
	#ifdef HAS_PROXIMITY
		proximity_loop();
	#endif

	#ifdef HAS_HALL
		hall_loop();
	#endif

	#ifdef HAS_IR
		ir_loop();
	#endif


	if (DEBUG) {
		if (millis() - logTS > DEBUG_INTERVAL) {
			logTS = millis();
			char data[124];
			sprintf(data, "DEBUG 3POS : %d || MOVING : %d || VFD : %d || last dir switch : %d | mode = %d | sensor = %lu | jamming=%d", switch_pos, moving, vfd_dir, last_switch, mode, SENSOR_DT, jamming);
			Serial.println(data);
		}
	}

	#ifdef HAS_RESET
		reset_loop();
		if (isReset) {
			resetSys();
			delay(1000);
			return;
		}
	#endif

	#ifdef HAS_TEMPERTURE
		temperature_loop();
		if (!temperatureOk()) {
			mode = FATAL;
			onFatal();
			return;
		}
	#endif

	if (switch_pos == FORWARD) {
		if (last_switch == STOP) {
			if (!isShredding() && mode == HALT) {
				startTS = millis();
				mode = STARTING;
			}
		}

		if (mode == STARTING) {
			if (millis() - startTS > STARTING_TIMEOUT) {
				if (isShredding()) {
					mode = SHREDDING;
				}
				else {
					mode = JAMMING;
					stop();
					return;
				}
			}
		}

		if (mode == SHREDDING) {
			if (!isShredding()) {
				mode = JAMMING;
				stop();
				#ifdef HAS_PROXIMTY
					proximity_reset();
				#endif
				return;
			}
			else {
				jamming = 0;
			}
		}

		if (mode == JAMMING) {
			if (jamming >= MAX_REVERSE_TRIALS) {
				mode = FATAL;
				stop();

				#ifdef HAS_PROXIMTY
					moving = false;
				#endif

				onFatal();
				return;
			}

			rev(true);
			mode = REVERSING;
			jamming++;
			reverseTS = millis();
			return;
		}

		if (mode == REVERSING) {
			if (millis() - reverseTS > REVERSING_TIMEOUT) {
				stop();
				startTS = millis();
				mode = STARTING;

				#ifdef HAS_PROXIMTY
					moving = false;
				#endif
			}
		}
	}

	#ifdef ALARM_SOUND
		if (mode == FATAL) {
			alarm();
		}
	#endif

	if ((mode == JAMMING || mode == FATAL || mode == REVERSING)) {
		if (switch_pos != STOP) {
			return;
		}
	}

	switch (switch_pos) {
		case FORWARD: {
			fwd(true);
			#ifdef HAS_STATUS
				setStatus(false);
			#endif
			break;
		}
		case REVERSE: {
			rev(true);
			#ifdef HAS_STATUS
				setStatus(false);
			#endif
			break;
		}
		case STOP: {
			stop();
			mode = HALT;
			jamming = 0;
			last_switch = STOP;
			#ifdef HAS_STATUS
				setStatus(true);
			#endif
			break;
		}
	}
	delay(100);
}
#endif
