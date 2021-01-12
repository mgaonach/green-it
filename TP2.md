# TP2

## Q1
En état normal : environ 1OmA

## Q2
Voir tableau excel

## Q3
9,7µA avec la config de la fonction enterSleepMod() :

```c++
void enterSleepMode() {

  flash.powerDown();

  LoRa.sleep();
  
  analogWrite(1, 0);

  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

};
```
