#include "arduino--.h"
#include "max7219.h"
#include "clock16.h"

typedef class _Max7219<Arduino::D7, Arduino::D6, Arduino::D5> Max7219;

int main(void)
    {
    Arduino::init();
    Max7219::init();

    Max7219::set(Max7219::ROW0, 1);   //  + - - - - - - -
    Max7219::set(Max7219::ROW1, 3);   //  + + - - - - - -
    Max7219::set(Max7219::ROW2, 7);   //  + + + - - - - -
    Max7219::set(Max7219::ROW3, 15);  //  + + + + - - - -
    Max7219::set(Max7219::ROW4, 31);  //  + + + + + - - -
    Max7219::set(Max7219::ROW5, 63);  //  + + + + + + - -
    Max7219::set(Max7219::ROW6, 127); //  + + + + + + + -
    Max7219::set(Max7219::ROW7, 255); //  + + + + + + + +

    while(true)
        {
        Clock16::sleep(500);
        }
    return 0;
    }
