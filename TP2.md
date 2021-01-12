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

## Q4
Mesure de température : pic à 12mA
Mesure endormi : ~45 µA

## Q5

(60000ms*40µA + 100ms*12000µA)/60100ms = 64,9µA
240000µAh/64,9µA = 3698h

Notre WhisperNode peut tenir 3698h sur la pile bouton, soit 154 jours.

## Q6

On mesure 5V.

## Q8 

Avec 2DB : 53.3 mA
Avec 17DB : 125 mA
Avec 20DB : 126.4 mA

En terme de consommation, il vaut mieux régler la puissance d'émission le plus bas possible, bien que cela limite la portée du signal.
