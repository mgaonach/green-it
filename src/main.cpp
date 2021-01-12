#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include <T2WhisperNode.h>
#include <LowPower.h>
#include <LoRa.h>
#include <RTClibExtended.h>
#include <ledNumber.cpp>

T2Flash flash;
RTC_DS3231 rtc;

void enterSleepMode() {

  flash.powerDown();

  LoRa.sleep();
  
  analogWrite(1, 0);

  for (int i=0; i <8; i++)  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  }
};

void sendRadioMessage() {
  const uint8_t radioBuf[10]={'0','1','2','3','4','5','6','7','8','9'};
  LoRa.beginPacket();
  LoRa.write(radioBuf,10);
  LoRa.endPacket();
}

void checkTemp() {

  float Ftemperature=rtc.getTemp();
  Serial.println((int) Ftemperature);

  LedNumber ledNumber = LedNumber(6, 9);
  ledNumber.printOnLed((int) Ftemperature);
};

void measureVoltage() {
  double voltageFTDI = (7.282 * analogRead(A7)) / 1024;
  Serial.print("Voltage FTDI : ");
  Serial.println(voltageFTDI);
}

void setup() {
  
  Serial.begin(9600);

  // SETUP RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  rtc.adjust(DateTime(__DATE__, __TIME__));   //set RTC date and time to COMPILE time

  // SETUP LoRA
  LoRa.setPins(10,7,2);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Q8
  // LoRa.setTxPower(2);
  // LoRa.setTxPower(20);

  // SETUP FLASH
  flash.init(T2_WPN_FLASH_SPI_CS);
  rtc = RTC_DS3231();
  
  // SETUP FOR VOLTAGE MEASURMENT
  analogReference(INTERNAL);
  pinMode(A7, INPUT);
  digitalWrite(14, HIGH);

  // Q7
  for (int i=0; i <100; i++)  {
    sendRadioMessage();
  }
};

void loop() {
  // checkTemp();
  // enterSleepMode();

  // Q6
  // measureVoltage();

  
};