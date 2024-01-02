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

unsigned char poleMetronom[8][8] = {{128, 128, 128, 128, 128, 128, 128, 128},
                                    {64, 64, 64, 64, 64, 64, 64, 64},
                                    {32, 32, 32, 32, 32, 32, 32, 32},
                                    {16, 16, 16, 16, 16, 16, 16, 16},
                                    {8, 8, 8, 8, 8, 8, 8, 8},
                                    {4, 4, 4, 4, 4, 4, 4, 4},
                                    {2, 2, 2, 2, 2, 2, 2, 2},
                                    {1, 1, 1, 1, 1, 1, 1, 1}};

unsigned char poleMetronomZpet[8][8] = {{1, 1, 1, 1, 1, 1, 1, 1},
                                        {2, 2, 2, 2, 2, 2, 2, 2},
                                        {4, 4, 4, 4, 4, 4, 4, 4},
                                        {8, 8, 8, 8, 8, 8, 8, 8},
                                        {16, 16, 16, 16, 16, 16, 16, 16},
                                        {32, 32, 32, 32, 32, 32, 32, 32},
                                        {64, 64, 64, 64, 64, 64, 64, 64},
                                        {128, 128, 128, 128, 128, 128, 128, 128}};

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
long casPoslednihoStisknuti = 0;
int hodnotaPot = 0;
int bpm = 0;

void displayAnimace(unsigned char pattern[8], int row, int bpm)
{
  for (int i = 0; i < 8; i++)
  {
    mx.setRow(row, i, pattern[i]);
  }
  float klickToMs = ((60000 / bpm) / 15.62575);
  delay(klickToMs);
  mx.clear();
}

void tlacitko()
{
  byte stavButton = digitalRead(BUTTON_PIN);
  if (stavButton == HIGH && posledniStav == LOW && (millis() - casPoslednihoStisknuti) > 200)
  {
    whileSmycka = !whileSmycka;
    casPoslednihoStisknuti = millis();

    if (!whileSmycka)
    {
      myDisplay.print(bpm);
    }
  }
}
void metronom()
{
  tone(BUZZER_PIN, 1318);
  delay(50);
  noTone(BUZZER_PIN);
  for (int x = 0; x <= 1; x++)
  {
    for (int i = 0; i < 7; i++)
    {
      tlacitko();
      displayAnimace(poleMetronomZpet[i], x, bpm);
      myDisplay.print(bpm);

    }
  }
  tone(BUZZER_PIN, 1760);
  delay(50);
  noTone(BUZZER_PIN);
  for (int x = 1; x >= 0; x--)
  {
    for (int i = 0; i < 7; i++)
    {
      tlacitko();
      displayAnimace(poleMetronom[i], x, bpm);
      myDisplay.print(bpm);
    }
  }
}

void loop()
{
  hodnotaPot = analogRead(POTENTIOMETER_PIN);
  bpm = map(hodnotaPot, 0, 1023, MIN_BPM, MAX_BPM);
  myDisplay.print(bpm);
  

  tlacitko();
  if (whileSmycka)
  {
    metronom();
  }
}
