#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include <bouton.cpp>

Bouton bouton4 = Bouton(4);

void setup() {
  
  Serial.begin(9600);

  // Q4
  Serial.println("Toto");
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

  // ===== Q7 =====
  bouton4.check();
  // ===============



}