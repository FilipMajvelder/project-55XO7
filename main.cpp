#include <Arduino.h>

// Definice pinů pro LED diody a tlačítko
const int ledPins[] = {2, 3, 4, 5, 6}; // Piny pro LED diody
const int buttonPin = 7;              // Pin pro tlačítko (D7)
const int speakerPin = 8;             // Pin pro reproduktor (D8)

// Rychlost metronomu v BPM (bílých za minutu)
const int bpm = 120;

// Interval mezi jednotlivými údery metronomu (ms)
const long beatInterval = 60000 / bpm;

// Proměnné pro sledování stavu tlačítka a metronomu
bool isMetronomeRunning = false;
bool lastButtonState = HIGH;
long lastButtonPressTime = 0;
long lastBeatTime = 0;
int currentBeat = 0;
bool increasing = true; // Příznak zda zvyšovat nebo snižovat index LED diody

// Binární sekvence pro rozsvěcování LED diod
int binarySequence[] = {0b10000, 0b01000, 0b00100, 0b00010, 0b00001};

void setup() {
  // Nastavení pinů pro LED diody jako výstupy
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Nastavení pinu pro tlačítko jako vstupu s pull-up rezistorem
  pinMode(buttonPin, INPUT_PULLUP);

  // Nastavení pinu pro reproduktor jako výstup
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // Přečtení stavu tlačítka
  bool buttonState = digitalRead(buttonPin);

  // Detekce stisku tlačítka
  if (buttonState == LOW && lastButtonState == HIGH && (millis() - lastButtonPressTime) > 200) {
    isMetronomeRunning = !isMetronomeRunning; // Přepnutí stavu metronomu
    lastButtonPressTime = millis();

    // Vypnutí metronomu
    if (!isMetronomeRunning) {
      for (int i = 0; i < 5; i++) {
        digitalWrite(ledPins[i], LOW);
      }
      increasing = true; // Resetování směru změny indexu LED diody
    }
  }

  // Spuštění metronomu
  if (isMetronomeRunning && (millis() - lastBeatTime) >= beatInterval) {
    lastBeatTime = millis();

    // Nastavení LED diod podle aktuálního stavu binární sekvence
    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPins[i], bitRead(binarySequence[currentBeat], i) ? HIGH : LOW);
    }

    // Přehrání zvuku na aktuálním úderu
    if (currentBeat == 0) {
      tone(speakerPin, 1000); // Frekvence tónu (1kHz)
      delay(50);              // Délka tónu (50ms)
      noTone(speakerPin);
    }

    // Aktualizace indexu LED diody podle směru
    if (increasing) {
      currentBeat++;
      if (currentBeat == 4) {
        increasing = false; // Po dosažení konce sekvence změní směr na snižování
      }
    } else {
      currentBeat--;
      if (currentBeat == 0) {
        increasing = true; // Po dosažení začátku sekvence změní směr na zvyšování
      }
    }
  }

  lastButtonState = buttonState;
}
