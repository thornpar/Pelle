// 
// 
// 

#include "OperationIndicator.h"

OperationIndicator::OperationIndicator() : ACTIVE(0,0,1), DELAYED_START(0,3,0)
{
	/*timeNow = 0;
	timeBefore = 0;*/
	timeLightBefore = 0;
	timeLightCurrent = 0;
	lightStatus = LIGHT_INACTIVE;
	previousLightStatus = LIGHT_INACTIVE;
}

void OperationIndicator::HandleContinousSignal()
{
	//Check if continous signal
	if (lightStatus == LIGHT_ACTIVE && operationState != OS_ACTIVE) {
		//Start recording time if the light just became active.
		timeLightCurrent = millis();
		if (previousLightStatus == LIGHT_INACTIVE) {
			timeLightBefore = timeLightCurrent;
		}

		if (timeLightCurrent - timeLightBefore > MS_DETERMINE_CONTINOUS_STATE) {
			timeLightBefore = timeLightCurrent;
			operationState = OS_ACTIVE;
			patternRecorder.Reset();
			patternRecorder.RegisterContinousSignal();
			Pattern p = patternRecorder.GetPattern();
			if (p == ACTIVE) {
				Serial.println("Viking Bio is operating normally.");
			}
		}
	}

	//If we are in continus state but light is no longer active.
	if (lightStatus == LIGHT_INACTIVE && operationState == OS_ACTIVE) {
		Serial.println("Viking Bio is inactive");
		operationState = OS_INACTIVE;
		patternRecorder.Reset();
		previousLightStatus = lightStatus;
	}
}

void OperationIndicator::HandleNewState()
{
	//timeNow = millis();
	//long elapsed = timeNow - timeBefore;

	if (lightStatus == LIGHT_INACTIVE) {
		operationState = OS_INACTIVE;
		patternRecorder.RegisterShortSignal();
		Pattern p = patternRecorder.GetPattern();
		if (p == DELAYED_START) {
			Serial.println("We are in delayed start");
			patternRecorder.Reset();
		}
		Serial.println("Short signal");
	}
	previousLightStatus = lightStatus;
}

void OperationIndicator::loop(float sensorValue)
{
	lightStatus = sensorValue > LIGHT_SENSITIVTY ? LIGHT_ACTIVE : LIGHT_INACTIVE;
	HandleContinousSignal();

	if (lightStatus == previousLightStatus) return; //Nothing has happened since the last time
	HandleNewState();
}

void OperationIndicator::setup()
{
	timeLightCurrent = millis();
	timeLightBefore = timeLightCurrent;
}
