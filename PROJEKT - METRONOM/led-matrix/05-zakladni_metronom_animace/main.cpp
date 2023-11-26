#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN D5  // or SCK  D5
#define DATA_PIN D7 // or MOSI D7
#define CS_PIN D4   // or SS   D4

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

unsigned char prvni[8] = {0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00};
unsigned char druha[8] = {0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00};
unsigned char treti[8] = {0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00};
unsigned char ctvrta[8] = {0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00};
unsigned char pata[8] = {0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00};

void setup()
{
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 0);
  mx.clear(); // Vymazání displeje
}

void loop()
{
  for (int row = 0; row < 8; row++)
  {
    mx.setRow(1, row, prvni[row]);
  }
  delay(500);
  mx.clear();
  for (int row = 0; row < 8; row++)
  {
    mx.setRow(1, row, druha[row]);
  }
  delay(500);
  mx.clear();
  for (int row = 0; row < 8; row++)
  {
    mx.setRow(1, row, treti[row]);
  }
  delay(500);
  mx.clear();
  for (int row = 0; row < 8; row++)
  {
    mx.setRow(0, row, ctvrta[row]);
  }
  delay(500);
  mx.clear();
  for (int row = 0; row < 8; row++)
  {
    mx.setRow(0, row, pata[row]);
  }
  delay(500);
  mx.clear();
  for (int row = 0; row < 8; row++)
  {
    mx.setRow(0, row, ctvrta[row]);
  }
  delay(500);
  mx.clear();
  for (int row = 0; row < 8; row++)
  {
    mx.setRow(1, row, treti[row]);
  }
  delay(500);
  mx.clear();
  for (int row = 0; row < 8; row++)
  {
    mx.setRow(1, row, druha[row]);
  }
  delay(500);
  mx.clear();
}
