#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   D5   // or SCK  D5
#define DATA_PIN  D7 // or MOSI D7
#define CS_PIN    D4  // or SS   D4

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);   // SPI hardware interface


unsigned char firstledfirstrow[8]={0b00000000, 0b11101110 , 0b00101010, 0b11101010, 0b10001010, 0b10101010, 0b11101110, 0b00000000};
int i=0; 

unsigned char secledfirstrow[8]={0b00000000, 0b11101110 , 0b00101010, 0b11101010, 0b10001010, 0b10101010, 0b11101110, 0b00000000};
int k=1;

void setup() 
{
     mx.begin();
}

void loop() 
{
         for (int j=0; j<8; j++)
         {
          mx.setRow(i, j, firstledfirstrow[j]);
          mx.setRow(k, j, secledfirstrow[j]);

         }
}
