
#include "OperationIndicator.h"
#include "FlameIndicator.h"
#include "ErrorIndicator.h"

#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;
ErrorIndicator errorIndicator;
FlameIndicator flameIndicator;
OperationIndicator operationIndicator;


void setup() {
  Wire.begin(D2, D1);
  Serial.begin(9600);
  errorIndicator.setup();
  flameIndicator.setup();
  operationIndicator.setup();
}

void loop() {
	float adc0, adc1, adc2;
	adc0 = ads.readADC_SingleEnded(0) * (5.0 / 1023.0);
	adc1 = ads.readADC_SingleEnded(1) * (5.0 / 1023.0);
	adc2 = ads.readADC_SingleEnded(2) * (5.0 / 1023.0);
	//Serial.println(adc0);
	operationIndicator.loop(adc0);
	//flameIndicator.loop(adc1);
	//errorIndicator.loop(adc2);

	delay(1);
}
