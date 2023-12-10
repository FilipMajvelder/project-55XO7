#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include "..\.pio\libdeps\nodemcu\MD_Parola\examples\Parola_Fonts\Parola_Fonts_data.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN D5  
#define DATA_PIN D7 
#define CS_PIN D4      
#define POTENTIOMETER_PIN D0
#define MIN_BPM 30            
#define MAX_BPM 210   

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

unsigned char poleMetronom[8][8] = {{0, 128, 128, 128, 128, 128, 128, 0},
                                    {0, 64, 64, 64, 64, 64, 64, 0},
                                    {0, 32, 32, 32, 32, 32, 32, 0},
                                    {0, 16, 16, 16, 16, 16, 16, 0},
                                    {0, 8, 8, 8, 8, 8, 8, 0},
                                    {0, 4, 4, 4, 4, 4, 4, 0},
                                    {0, 2, 2, 2, 2, 2, 2, 0},
                                    {0, 1, 1, 1, 1, 1, 1, 0}};

unsigned char poleMetronomZpet[8][8] = {{0, 1, 1, 1, 1, 1, 1, 0},
                                        {0, 2, 2, 2, 2, 2, 2, 0},
                                        {0, 4, 4, 4, 4, 4, 4, 0},
                                        {0, 8, 8, 8, 8, 8, 8, 0},
                                        {0, 16, 16, 16, 16, 16, 16, 0},
                                        {0, 32, 32, 32, 32, 32, 32, 0},
                                        {0, 64, 64, 64, 64, 64, 64, 0},
                                        {0, 128, 128, 128, 128, 128, 128, 0}};

void displayPattern(unsigned char pattern[8], int row, float klickToMs)
{
  for (int i = 0; i < 8; i++)
  {
    mx.setRow(row, i, pattern[i]);
  }
  delay(klickToMs);
  mx.clear();
}

void setup()
{
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5);
  mx.clear();
  myDisplay.begin();
  myDisplay.setIntensity(5);
  myDisplay.displayClear();
  myDisplay.setFont(cislafont);
}

void loop() {
  int hodnotaPot = 0;
  int bpm = 0;
  hodnotaPot = analogRead(POTENTIOMETER_PIN);
  bpm = map(hodnotaPot, 0, 1023, MIN_BPM, MAX_BPM);
  myDisplay.setTextAlignment(PA_LEFT);
  myDisplay.print(bpm);

  float klickToMs = ((60000.0 / bpm) / 16);

  for (int x = 0; x <= 1; x++) {
    for (int i = 0; i < 8; i++) {
      displayPattern(poleMetronomZpet[i], x, klickToMs);
      myDisplay.print(bpm);
    }
  }
  for (int x = 1; x >= 0; x--) {
    for (int i = 0; i < 8; i++) {
      displayPattern(poleMetronom[i], x, klickToMs);
      myDisplay.print(bpm);
    }
  } 
}

