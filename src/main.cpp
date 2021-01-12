#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include <T2WhisperNode.h>
#include <LowPower.h>
#include <LoRa.h>

T2Flash flash;

void enterSleepMode() {

  flash.powerDown();

  LoRa.sleep();
  
  analogWrite(1, 0);

  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

};

void setup() {
  
  Serial.begin(9600);

  LoRa.setPins(10,7,2);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  flash.init(T2_WPN_FLASH_SPI_CS);

  enterSleepMode();
};

void loop() {

};