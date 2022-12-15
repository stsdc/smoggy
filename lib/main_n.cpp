#include <Arduino.h>

#include "../include/pins.h"

void setup() {
    Serial.begin(115200);

}

void loop() {
    // put your main code here, to run repeatedly:

    digitalWrite(PIN_LED_INBUILT, HIGH);
    delay(1000);
    digitalWrite(PIN_LED_INBUILT, LOW);
    delay(1000);

}