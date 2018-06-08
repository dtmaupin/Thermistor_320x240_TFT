#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// These are the pins used for the UNO
// for Due/Mega/Leonardo use the hardware SPI pins (which are different)
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _dc 9
#define _rst 8

// Use hardware SPI
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);


int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
Serial.begin(9600);
tft.begin();
tft.setRotation(3);
dispfixedText();
}

void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  /*Serial.print("R1: ");
  Serial.print(R1);
  Serial.print(" R2: ");
  Serial.println(R2);
  Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C"); */
  updateText();
    

  delay(25);
}
unsigned long dispfixedText() {
  tft.fillScreen(ILI9340_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9340_WHITE);  tft.setTextSize(2);
  tft.println("Thermistor Temp");
  tft.setCursor(0, 40);
  tft.setTextColor(ILI9340_YELLOW); tft.setTextSize(2);
  tft.print("Temp F: ");
  return micros() - start;
}
unsigned long updateText() {
  //tft.fillScreen(ILI9340_BLACK);
  unsigned long start = micros();
  tft.setCursor(100, 40);
  tft.fillRect(95, 40, 100, 22, ILI9340_BLACK);
  tft.setTextColor(ILI9340_RED);    tft.setTextSize(3);
  tft.println(Tf);
  tft.println();
  return micros() - start;
}




