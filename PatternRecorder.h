// PatternRecorder.h

#ifndef _PATTERNRECORDER_h
#define _PATTERNRECORDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "States.h"
#include "Pattern.h"

class PatternRecorder {
	public:
		PatternRecorder();
		void Restart();
		void Reset();
		void RegisterLongSignal();
		void RegisterShortSignal();
		void RegisterContinousSignal();
		bool GotPattern();
		Pattern GetPattern();
		short longSignal;
		short shortSignal;
		short continousSignal;
	private:
		
		bool patternComplete;
		Pattern finishedPattern;
};

#endif

