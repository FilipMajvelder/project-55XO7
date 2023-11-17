#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "..\.pio\libdeps\nodemcu\MD_Parola\examples\Parola_Fonts\Parola_Fonts_data.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   D5   // or SCK  D5
#define DATA_PIN  D7 // or MOSI D7
#define CS_PIN    D6  // or SS   D4

int bpm = 120;
long beatInterval = 60000 / bpm;

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


void setup() {
  mx.begin();
  myDisplay.begin();
  myDisplay.setIntensity(5);
  myDisplay.displayClear();
  myDisplay.setFont(cislafont);
}

void loop() {
  myDisplay.setTextAlignment(PA_LEFT);
  myDisplay.print(bpm);
}

/* delay((1 / (bpm / 60)) * 1000); */ 