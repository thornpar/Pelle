#ifndef ErrorIndicator_h
#define ErrorIndicator_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "States.h"
#include "PatternRecorder.h"
#include "Pattern.h"
#include "Globals.h"


class ErrorIndicator{
	public:
		ErrorIndicator();
		void loop(float sensorValue);
		void CheckResetAlarm(long howLongBeforeResetAlarm);
		void HandleNewState();
		void setup();
		
	private:
		PatternRecorder patternRecorder;
		WarningState warningState;
		LightState currentState;
		LightState previousState;
		//Patterns
		const Pattern HIGH_TEMPERATURE_PIPE;
		const Pattern FAILED_START;
		const Pattern HIGH_SURROUNDING_TEMPERATURE;
		const Pattern FAN_FAILURE;
		const Pattern OVERPRESSURE_BURNING_CHAMBER;
		const Pattern STARTELEMENT_DISFUNCTION;
		long timeNow;
		long timeBefore;
};

#endif
