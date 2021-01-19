#include <Arduino.h>

class Bouton
{

public:
    Bouton()
    {
    }

    Bouton(int pin)
    {
        numPin = pin;
    }

    int getNumber()
    {
        if (millis() - lastClick > 500) {
            int res = nbPressed;
            nbPressed = 0;
            return res;
        }
        else {
            return 0;
        };
    };

    void check()
    {
        if (digitalRead(numPin) == HIGH)
        {
            isPressed = true;
        }
        else if (isPressed)
        {
            isPressed = false;
            lastClick = millis();
            Serial.println("Pressed");
            nbPressed++;
        };
    };

private:
    int nbPressed = 0;
    int numPin;
    boolean isPressed = false;
    unsigned long lastClick;
};
