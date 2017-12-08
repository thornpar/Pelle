#include "ErrorIndicator.h"

ErrorIndicator::ErrorIndicator()
	:	HIGH_TEMPERATURE_PIPE(1,0,0),
		FAILED_START(1,2,0),
		HIGH_SURROUNDING_TEMPERATURE(1,3,0),
		FAN_FAILURE(1,4,0),
		OVERPRESSURE_BURNING_CHAMBER(1,5,0),
		STARTELEMENT_DISFUNCTION(0,8,0)
{
	currentState = LIGHT_INACTIVE;
	previousState = LIGHT_INACTIVE;
	timeNow = 0;
	timeBefore = 0;
	warningState = WS_INACTIVE;
}	

void ErrorIndicator::loop(float sensorValue){
	currentState = sensorValue > LIGHT_SENSITIVTY ? LIGHT_ACTIVE : LIGHT_INACTIVE;
	CheckResetAlarm(MS_RESET_ALARM);
	
	if(currentState == previousState) return; //Nothing has happened since the last time
	HandleNewState();
}

void ErrorIndicator::CheckResetAlarm(long howLongBeforeResetAlarm)
{
	if (warningState != WS_INACTIVE && millis() - timeBefore > howLongBeforeResetAlarm) {
		Serial.println("Alarm is considered to have been fixed");
		warningState = WS_INACTIVE;
		patternRecorder.Reset();
	}
}

void ErrorIndicator::HandleNewState()
{
	timeNow = millis();
	long elapsed = timeNow - timeBefore;

	if (currentState == LIGHT_INACTIVE) {
		if (elapsed > MS_LONG_SIGNAL_DEFINITON) {
			patternRecorder.RegisterLongSignal();
			Serial.println("Long signal");
		}
		else {
			patternRecorder.RegisterShortSignal();
			Serial.println("Short signal");
		}

		if (patternRecorder.GotPattern()) {
			Pattern tempPattern = patternRecorder.GetPattern();
			if (tempPattern == HIGH_TEMPERATURE_PIPE) {
				Serial.println("HIGH_TEMPERATURE_PIPE");
				warningState = WS_HIGH_TEMPERATURE_PIPE;
			}
			else if (tempPattern == FAILED_START) {
				Serial.println("FAILED_START");
				warningState = WS_FAILED_START;
			}
			else if (tempPattern == HIGH_SURROUNDING_TEMPERATURE) {
				Serial.println("HIGH_SURROUNDING_TEMPERATURE");
				warningState = WS_HIGH_SURROUNDING_TEMPERATURE;
			}
			else if (tempPattern == FAN_FAILURE) {
				Serial.println("FAN_FAILURE");
				warningState = WS_FAN_FAILURE;
			}
			else if (tempPattern == OVERPRESSURE_BURNING_CHAMBER) {
				Serial.println("OVERPRESSURE_BURNING_CHAMBER");
				warningState = WS_OVERPRESSURE_BURNING_CHAMBER;
			}
			else if (tempPattern == STARTELEMENT_DISFUNCTION) {
				Serial.println("STARTELEMENT_DISFUNCTION");
				warningState = WS_OVERPRESSURE_BURNING_CHAMBER;
			}
			else {
				Serial.println("Could not determine pattern :(");
				Serial.println("Short"); Serial.print(tempPattern.shortSignals);
				Serial.println("Long"); Serial.print(tempPattern.longSignals);
				Serial.println("Continous"); Serial.print(tempPattern.continousSignal);

				warningState = WS_OVERPRESSURE_BURNING_CHAMBER;
			}
			patternRecorder.Restart();
		}
	}

	timeBefore = timeNow;
	previousState = currentState;
}

void ErrorIndicator::setup(){
	timeNow = millis();
	timeBefore = timeNow;
}