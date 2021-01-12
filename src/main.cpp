#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include <bouton.cpp>
#include <T2WhisperNode.h>
#include <ledNumber.cpp>
#include <LowPower.h>

void setup() {
  
  Serial.begin(9600);

  LowPower.powerDown(SLEEP_FOREVER, ADC_ON, BOD_ON);

};

void loop() {

};