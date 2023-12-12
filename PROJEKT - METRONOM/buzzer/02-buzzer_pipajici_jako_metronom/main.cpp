#include <Arduino.h>

const int buttonPin = D2;
const int speakerPin = D3;

int bpm = 150;
long beatInterval = 60000 / bpm

bool isMetronomeRunning = false;
bool lastButtonState = HIGH;
long lastButtonPressTime = 0;
long lastBeatTime = 0;
int currentBeat = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW && lastButtonState == HIGH && (millis() - lastButtonPressTime) > 200) {
    isMetronomeRunning = !isMetronomeRunning;
    lastButtonPressTime = millis();
    
    // Reset čítače úderů při novém spuštění metronomu
    if (isMetronomeRunning) {
      currentBeat = 0;
    }
  }
  
  if (isMetronomeRunning && (millis() - lastBeatTime) >= beatInterval) {
    lastBeatTime = millis();
    
    if (currentBeat == 0 || currentBeat == 4) {
      tone(speakerPin, 1318);
    } else {
      tone(speakerPin, 1760);
    }
    
    delay(50);
    noTone(speakerPin);
    
    currentBeat++;
    if (currentBeat > 7) {
      currentBeat = 0;
    }
  }
  
  lastButtonState = buttonState;
}
