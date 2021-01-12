#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include <bouton.cpp>
#include <T2WhisperNode.h>
#include <ledNumber.cpp>

// ===== Q8 =====
// Bouton bouton4 = Bouton(4);
// Bouton bouton5 = Bouton(5);
// ===============

void setup() {
  
  Serial.begin(9600);

  // Q4
  Serial.println("Toto");
  LedNumber ledNumber = LedNumber(6,9);
  ledNumber.printNumber(24);
}

void loop() {


  // ===== Q5 =====
  
  // delay(100);
  // digitalWrite(6, LOW);
  // delay(1000);
  // digitalWrite(9, HIGH);
  // delay(100);
  // digitalWrite(9, LOW);
  // delay(1000);
  // ===============

  // ===== Q6 =====
  // digitalWrite(6, digitalRead(4));
  // digitalWrite(9, digitalRead(5));
  // ===============

  // ===== Q8 =====
  // bouton4.check();
  // bouton5.check();
  // if (bouton5.getNumber() > 0) {
  //   Serial.println(bouton4.getNumber());
  // }
  // ===============

  

}