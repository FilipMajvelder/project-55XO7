#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include "..\.pio\libdeps\nodemcu\MD_Parola\examples\Parola_Fonts\Parola_Fonts_data.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN D5  // or SCK  D5
#define DATA_PIN D7 // or MOSI D7
#define CS_PIN D4   // or SS   D4
#define BUTTON_PIN D1
#define BUZZER_PIN D2

#define BPM 120

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

float klickToMs = ((60000 / BPM) / 18.5);

byte lastButtonState = LOW;
int stav = 0;

int pom = 128;
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

void displayPattern(unsigned char pattern[8], int row)
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
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5);
  mx.clear();
  myDisplay.begin();
  myDisplay.setIntensity(5);
  myDisplay.displayClear();
  myDisplay.setFont(cislafont);
  Serial.begin(9600);
  
}

void loop()
{
  Serial.println(stav);
  myDisplay.setTextAlignment(PA_LEFT);
  myDisplay.print(BPM);
  byte buttonState = digitalRead(BUTTON_PIN);

  if(buttonState == HIGH && stav == 0)
  {
    stav = 1;
  }

  while (stav == 1)
  {
    if (buttonState == HIGH && stav == 1)
  {
    stav = 0;
  }
    tone(BUZZER_PIN, 1318);
    delay(50);
    noTone(BUZZER_PIN);
    for (int x = 0; x <= 1; x++)
    {
      for (int i = 0; i < 8; i++)
      {
        displayPattern(poleMetronomZpet[i], x);
        myDisplay.print(BPM);
      }
    }
    tone(BUZZER_PIN, 1760);
    delay(50);
    noTone(BUZZER_PIN);
    for (int x = 1; x >= 0; x--)
    {
      for (int i = 0; i < 8; i++)
      {
        displayPattern(poleMetronom[i], x);
        myDisplay.print(BPM);
      }
    }
  }
}
