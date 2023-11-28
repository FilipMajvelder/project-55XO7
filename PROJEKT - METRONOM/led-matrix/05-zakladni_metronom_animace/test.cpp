#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN D5  // or SCK  D5
#define DATA_PIN D7 // or MOSI D7
#define CS_PIN D4   // or SS   D4

#define BPM 120

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int klickToMs = (60000 / BPM);

unsigned char poleMetronom[8][8] = {{0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00},
                                    {0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00},
                                    {0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00},
                                    {0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00},
                                    {0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00},
                                    {0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00},
                                    {0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00},
                                    {0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00}};

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
}

void loop()
{
  for (int x = 3; x >= 0; x--)
  {
    for (int i = 0; i < 8; i++)
      displayPattern(poleMetronom[i], x);
  }
}
