// OperationIndicator.h

#ifndef _OPERATIONINDICATOR_h
#define _OPERATIONINDICATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "States.h"
#include "PatternRecorder.h"
#include "Pattern.h"
#include "Globals.h"


class OperationIndicator
{
 private:
	void HandleContinousSignal();
	void HandleNewState();
	OperationState operationState;
	PatternRecorder patternRecorder;
	LightState lightStatus;
	LightState previousLightStatus;
	const Pattern ACTIVE;
	const Pattern DELAYED_START;
	//long timeNow;
	//long timeBefore;
	long timeLightCurrent;
	long timeLightBefore;

 public:
	OperationIndicator();
	void loop(float sensorValue);
	void setup();
};

#endif

