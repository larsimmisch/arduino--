#include "arduino--.h"
#define CLOCK_NO_ISR
#include "clock16.h"
#include "ringbuffer.h"
#include "eventwait.h"

/** This test program blinks the LED on D13/B5 by sending a message from 
    the timer0 overflow ISR to the main program.
 */

typedef _Ringbuffer<bool, 4> BoolBuffer;

_EventWait<Clock16, BoolBuffer> BoolQueue;

ISR(TIMER0_OVF_vect)
{
    static int count = 0;
    static bool v = true;

    ++count;

    if (count == 1000) {
        BoolQueue.push(v);
        v = !v;
        count = 0;
    }

    clock16_isr();
}

int main(void)
{
    Arduino::init();
    Pin::B5::modeOutput();

    for(;;) {

        BoolQueue.wait_event();

        if (!BoolQueue.empty()) {

            if (BoolQueue.front()) {
                Pin::B5::set();
            }
            else {
                Pin::B5::clear();
            }

            BoolQueue.pop();
        }
    }

    return 0;
}
