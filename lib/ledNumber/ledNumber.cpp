#include <T2WhisperNode.h>

class LedNumber {

    public:

    LedNumber(int ledDizaine, int ledUnits) {
        dizaine = T2Led(ledDizaine);
        units = T2Led(ledUnits);
    }

    void printNumber(unsigned int number) {
        dizaine.setBlink(100, 100, number/10);
        units.setBlink(100, 100, number%10);

        dizaine.run();
        units.run();
    };

    private:
        T2Led dizaine;
        T2Led units;
};