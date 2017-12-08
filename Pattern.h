// Pattern.h

#ifndef _PATTERN_h
#define _PATTERN_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Pattern
{	

public:
	Pattern(short longSignals, short shortSignals, short continousSignal = 0) {
		this->longSignals = longSignals;
		this->shortSignals = shortSignals;
		this->continousSignal = continousSignal;
	}

	short longSignals;
	short shortSignals;
	short continousSignal;

	bool operator == (const Pattern& pattern) const {
		return pattern.longSignals == this->longSignals
			&& pattern.shortSignals == this->shortSignals
			&& pattern.continousSignal == this->continousSignal;
	}
};

#endif