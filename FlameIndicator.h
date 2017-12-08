// FeederIndicator.h

#ifndef _FLAMEINDICATOR_h
#define _FLAMEINDICATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "States.h"
#include "PatternRecorder.h"
#include "Pattern.h"
#include "Globals.h"

class FlameIndicator
{
 private:
	 long timeLightCurrent;
	 long timeLightBefore;
	 FlameState flameState;
	 LightState lightStatus;
	 LightState previousLightStatus;
	 PatternRecorder patternRecorder;
	 const Pattern START_PHASE;
	 const Pattern BURNING;
	 void HandleContinousSignal();
	 void HandleNewState();

 public:
	 FlameIndicator();
	 void loop(float sensorValue);
	 void setup();
};

#endif

