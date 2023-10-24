#include <Arduino.h>

const int ledPins[] = {2, 3, 4, 5, 6};
const int buttonPin = 7;
const int incBpmButtonPin = 9;
const int decBpmButtonPin = 10;
const int speakerPin = 8;

int bpm = 120;
long beatInterval = 60000 / bpm;

bool isMetronomeRunning = false;
bool lastButtonState = HIGH;
long lastButtonPressTime = 0;
long lastBeatTime = 0;
int currentBeat = 0;
int beatDirection = 1; // 1 pro jednu stranu, -1 pro druhou stranu

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(incBpmButtonPin, INPUT_PULLUP);
  pinMode(decBpmButtonPin, INPUT_PULLUP);

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
    }
  }

  if (digitalRead(incBpmButtonPin) == LOW) {
    if (bpm < 250) {
      bpm += 10;
      beatInterval = 60000 / bpm;
    }
  }

  if (digitalRead(decBpmButtonPin) == LOW) {
    if (bpm > 70) {
      bpm -= 10;
      beatInterval = 60000 / bpm;
    }
  }

  if (isMetronomeRunning && (millis() - lastBeatTime) >= beatInterval) {
    lastBeatTime = millis();
    digitalWrite(ledPins[currentBeat], HIGH);

    if (currentBeat == 0 || currentBeat == 4) {
      tone(speakerPin, 1318,51); 
    } else {
      tone(speakerPin, 1760); 
    }
    delay(50);
    noTone(speakerPin);

    digitalWrite(ledPins[currentBeat], LOW);
    
    currentBeat += beatDirection;
    
    if (currentBeat == 0 || currentBeat == 4) {
      beatDirection *= -1;
    }
  }

  lastButtonState = buttonState;
}
