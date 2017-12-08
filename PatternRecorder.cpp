// 
// 
// 

#include "PatternRecorder.h"

PatternRecorder::PatternRecorder() : finishedPattern(0,0,0)
{
	longSignal = 0;
	shortSignal = 0;
	continousSignal = 0;
	patternComplete = false;
}

void PatternRecorder::Restart()
{
	Serial.println("Restarting recorder");
	longSignal = 1;
	shortSignal = 0;
	finishedPattern.longSignals = 0;
	finishedPattern.shortSignals = 0;
	patternComplete = false;
}

void PatternRecorder::Reset()
{
	Serial.println("Resetting recorder");
	Restart();
	longSignal = 0;
	continousSignal = 0;
}

void PatternRecorder::RegisterLongSignal()
{
	if (longSignal != 0) {
		patternComplete = true;
		finishedPattern.longSignals = longSignal;
		finishedPattern.shortSignals = shortSignal;
		return;
	}
	longSignal += 1;
}

void PatternRecorder::RegisterShortSignal()
{
	if (shortSignal >= 7) {
		patternComplete = true;
		finishedPattern.longSignals = longSignal;
		finishedPattern.shortSignals = shortSignal;
	}
	shortSignal += 1;
	//Serial.print("RegisterShortSignal, shortSignals");
	//Serial.println(shortSignal);
}

void PatternRecorder::RegisterContinousSignal()
{
	continousSignal = 1;
	patternComplete = true;
}

bool PatternRecorder::GotPattern()
{
	return patternComplete;
}

Pattern PatternRecorder::GetPattern()
{
	finishedPattern.longSignals = longSignal;
	finishedPattern.shortSignals = shortSignal;
	finishedPattern.continousSignal = continousSignal;

	//Serial.print("GetPattern, shortSignals");
	//Serial.println(finishedPattern.shortSignals);
	return finishedPattern;
}
