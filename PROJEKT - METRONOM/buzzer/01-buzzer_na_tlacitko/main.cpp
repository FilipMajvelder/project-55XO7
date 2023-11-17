#include <Arduino.h>

const int buttonPin = D2; 
const int buzzerPin = D3; 

void setup() {
 Serial.begin(115200);
 delay(10);

 pinMode(buttonPin, INPUT_PULLUP);
 pinMode(buzzerPin, OUTPUT);
}

void loop() {
 int buttonState = digitalRead(buttonPin);

 if (buttonState == LOW) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100); 
 }
}
