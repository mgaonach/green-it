#include <T2WhisperNode.h>

class LedNumber
{

public:
    LedNumber(int ledDizaine, int ledUnits)
    {
        dizaine = T2Led(ledDizaine);
        units = T2Led(ledUnits);
    }

    void printOnLed(int temp)
    {
        int i = 0;
        for (i = 0; i < (temp / 10); i++)
        {
            dizaine.turnOn();
            delay(500);
            dizaine.turnOff();
            delay(500);
        }
        for (i = 0; i < (temp % 10); i++)
        {
            units.turnOn();
            delay(500);
            units.turnOff();
            delay(500);
        }
    }

private:
    T2Led dizaine;
    T2Led units;
};