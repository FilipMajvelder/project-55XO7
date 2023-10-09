#include <Arduino.h>

const int ledPins[] = {2, 3, 4, 5, 6}; 
const int buttonPin = 7;              
const int speakerPin = 8;           

const int bpm = 120;
const long beatInterval = 60000 / bpm;

bool isMetronomeRunning = false;
bool lastButtonState = HIGH;
long lastButtonPressTime = 0;
long lastBeatTime = 0;
int currentBeat = 0;
bool increasing = true; 

int binarySequence[] = {0b10000, 0b01000, 0b00100, 0b00010, 0b00001};

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH && (millis() - lastButtonPressTime) > 200) {
    isMetronomeRunning = !isMetronomeRunning;
    lastButtonPressTime = millis();
    if (!isMetronomeRunning) {
      for (int i = 0; i < 5; i++) {
        digitalWrite(ledPins[i], LOW);
      }
      increasing = true; 
    }
  }
  
  if (isMetronomeRunning && (millis() - lastBeatTime) >= beatInterval) {
    lastBeatTime = millis();
    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPins[i], bitRead(binarySequence[currentBeat], i) ? HIGH : LOW);
    }
  
  /** if (currentBeat == 0) {
      tone(speakerPin, 1000); 
      delay(50);             
      noTone(speakerPin);
    } **/

    if (increasing) {
      currentBeat++;
      if (currentBeat == 4) {
        increasing = false; 
      }
    } else {
      currentBeat--;
      if (currentBeat == 0) {
        increasing = true; /
      }
    }
  }

  lastButtonState = buttonState;
}
