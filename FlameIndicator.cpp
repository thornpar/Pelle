// 
// 
// 

#include "FlameIndicator.h"

FlameIndicator::FlameIndicator() : 
	START_PHASE(0,3,0), 
	BURNING(0, 0, 1)
{
	flameState = FS_INACTIVE;
	lightStatus = LIGHT_INACTIVE;
}

void FlameIndicator::loop(float sensorValue)
{
	lightStatus = sensorValue > LIGHT_SENSITIVTY ? LIGHT_ACTIVE : LIGHT_INACTIVE;
	HandleContinousSignal();

	if (lightStatus == previousLightStatus) return; //Nothing has happened since the last time
	HandleNewState();
}

void FlameIndicator::HandleNewState()
{
	if (lightStatus == LIGHT_INACTIVE) {
		flameState = FS_INACTIVE;

		patternRecorder.RegisterShortSignal();
		Pattern p = patternRecorder.GetPattern();
		if (p == START_PHASE) {
			Serial.println("We are in startphase");
			patternRecorder.Reset();
		}
		Serial.println("Short signal");
	}
	previousLightStatus = lightStatus;
}

void FlameIndicator::HandleContinousSignal()
{
	//Check if continous signal
	if (lightStatus == LIGHT_ACTIVE && flameState != FS_CONTINOUS) {
		//Start recording time if the light just became active.
		timeLightCurrent = millis();
		if (previousLightStatus == LIGHT_INACTIVE) {
			timeLightBefore = timeLightCurrent;
		}

		if (timeLightCurrent - timeLightBefore > MS_DETERMINE_CONTINOUS_STATE) {
			timeLightBefore = timeLightCurrent;
			flameState = FS_CONTINOUS;
			patternRecorder.Reset();
			patternRecorder.RegisterContinousSignal();
			Pattern p = patternRecorder.GetPattern();
			if (p == BURNING) {
				Serial.println("Flame is burning");
			}
		}
	}

	//If we are in continus state but light is no longer active.
	if (lightStatus == LIGHT_INACTIVE && flameState == FS_CONTINOUS) {
		Serial.println("Flame no longer burning");
		flameState = FS_INACTIVE;
		patternRecorder.Reset();
		previousLightStatus = lightStatus;
	}
}

void FlameIndicator::setup()
{	
	timeLightCurrent = millis();
	timeLightBefore = timeLightCurrent;
}
