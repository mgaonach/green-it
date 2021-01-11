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
        int res = nbPressed;
        nbPressed = 0;
        return res;
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
            nbPressed++;
            Serial.println(getNumber());
        };
    };

private:
    int nbPressed = 0;
    int numPin;
    boolean isPressed = false;
};
