#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include "..\.pio\libdeps\nodemcu\MD_Parola\examples\Parola_Fonts\Parola_Fonts_data.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN D5  
#define DATA_PIN D7 
#define CS_PIN D4   
#define BUTTON_PIN D1
#define BUZZER_PIN D2
#define POTENTIOMETER_PIN A0
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

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5);
  mx.clear();
  myDisplay.begin();
  myDisplay.setIntensity(5);
  myDisplay.displayClear();
  myDisplay.setFont(cislafont);
  myDisplay.setTextAlignment(PA_LEFT);
}

bool whileSmycka = false;
bool posledniStav = LOW;
int hodnotaPot = 0;
int bpm = 0;

void displayPattern(unsigned char pattern[8], int row, int bpm)
{
  for (int i = 0; i < 8; i++)
  {
    mx.setRow(row, i, pattern[i]);
  }
  float klickToMs = ((60000 / bpm) / 18.5);
  delay(klickToMs);
  mx.clear();
}

void loop()
{
  byte stavButton = digitalRead(BUTTON_PIN);
  hodnotaPot = analogRead(POTENTIOMETER_PIN);
  bpm = map(hodnotaPot, 0, 1023, MIN_BPM, MAX_BPM);
  myDisplay.print(bpm);

  if (stavButton != posledniStav) {
    delay(50); 
    stavButton = digitalRead(BUTTON_PIN); 

    if (stavButton != posledniStav) {
      posledniStav = stavButton; 

      if (stavButton == LOW) {
        if (!whileSmycka) {
          whileSmycka = true; 
        } else {
          whileSmycka = false; 
        }
      }
    }
  }

  if (whileSmycka)
  {
    tone(BUZZER_PIN, 1318);
    delay(50);
    noTone(BUZZER_PIN);
    for (int x = 0; x <= 1; x++)
    {
      for (int i = 0; i < 8; i++)
      {
        displayPattern(poleMetronomZpet[i], x, bpm);
        myDisplay.print(bpm);
      }
    }
    tone(BUZZER_PIN, 1760);
    delay(50);
    noTone(BUZZER_PIN);
    for (int x = 1; x >= 0; x--)
    {
      for (int i = 0; i < 8; i++)
      {
        displayPattern(poleMetronom[i], x, bpm);
        myDisplay.print(bpm);
      }
    }
  }
}
