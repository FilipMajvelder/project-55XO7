#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include "..\.pio\libdeps\nodemcu\MD_Parola\examples\Parola_Fonts\Parola_Fonts_data.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN D5  // or SCK  D5
#define DATA_PIN D7 // or MOSI D7
#define CS_PIN D4   // or SS   D4

#define BPM 120

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

float klickToMs = ((60000 / BPM) / 32);

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
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5);
  mx.clear();
  myDisplay.begin();
  myDisplay.setIntensity(5);
  myDisplay.displayClear();
  myDisplay.setFont(cislafont);
}

void loop()
{
  myDisplay.setTextAlignment(PA_CENTER);
  for (int x = 0; x <= 3; x++)
  {
    for (int i = 0; i < 8; i++)
    {
      displayPattern(poleMetronomZpet[i], x);
      myDisplay.print(BPM);
    }
  }

  for (int x = 3; x >= 0; x--)
  {
    for (int i = 0; i < 8; i++)
    {
      displayPattern(poleMetronom[i], x);
      myDisplay.print(BPM);
    }   
  }
}
