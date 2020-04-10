#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_INA219.h>
#include <Adafruit_SSD1306.h>
#include "configs.h"

Adafruit_INA219 ina219;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void initDisplay();
void printInfo(float,float,float);
void printLogo();
void setup(void) 
{
  Wire.begin(D4,D1);
  Serial.begin(9600);
  ina219.begin();
  initDisplay();
  printLogo();
}

void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  printInfo(loadvoltage,current_mA,power_mW);
  delay(100);

}

void initDisplay(){
  display.begin();
  display.clearDisplay();
  display.display();
  display.setRotation(2);
}

void printInfo(float tensao,float corrente, float potencia){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,1);             
  display.print("Voltage: ");
  display.print(tensao);
  display.println(" V");
  display.print("Current: ");
  display.print(corrente);
  display.println(" mA");
  display.print("Power: ");
  display.print(potencia);
  display.println(" mW");
  display.display();
}

void printLogo(){
  display.clearDisplay();
    display.drawBitmap(0, 0, voltimeter, 32, 32, WHITE);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(38,16);
    display.println("Iot Power Meter");
    display.display();
    delay(3000);
}