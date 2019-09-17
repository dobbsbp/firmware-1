#ifndef FEATURES_H
#define FEATURES_H

#ifdef HAS_TEMPERTURE
	#include "temperature.h"
#endif

#ifdef ALARM_SOUND
	#include "alarm.h"
#endif

#ifdef HAS_HALL
	#include "hall.h"
#endif

#ifdef HAS_PROXIMITY
	#include "proximity.h"
#endif

#ifdef HAS_STATUS
	#include "status.h"
#endif

#ifdef HAS_RESET
	#include "reset.h"
#endif

#ifdef HAS_IR
	#include "ir.h"
#endif

#endif