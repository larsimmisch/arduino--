#include "arduino--.h"
#include "max7219.h"
#include "clock16.h"

typedef class _Max7219<Arduino::D10, Arduino::D8, Arduino::D9> Max7219;

int main(void)
    {
    Arduino::init();
    Max7219::init();

    Max7219::set(Max7219::ROW7, 0);   //  - - - - - - - -
    Max7219::set(Max7219::ROW6, 208); //  - - - - + - + +
    Max7219::set(Max7219::ROW5, 80);  //  - - - - + - + -
    Max7219::set(Max7219::ROW4, 213); //  + - + - + - + +
    Max7219::set(Max7219::ROW3, 85);  //  + - + - + - + -
    Max7219::set(Max7219::ROW2, 86);  //  - + - - + - + -
    Max7219::set(Max7219::ROW1, 0);   //  - - - - - - - -
    Max7219::set(Max7219::ROW0, 0);   //  - - - - - - - -

    while(true)
        {
        for (byte i = Max7219::ROW0; i <= Max7219::ROW7; ++i)
            {
            for (byte j = 0; j < 8; ++j)
                {
                Max7219::set(i, 1 << j);
                Clock16::sleep(50);
                Max7219::set(i, 0);                
                }
            }
        }
    return 0;
    }
