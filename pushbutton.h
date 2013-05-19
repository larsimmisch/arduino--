// -*- mode: c++; indent-tabs-mode: nil; -*-

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include "arduino--.h"

template<class Timer_, class Pin_, int debounce_>
class PushButton
    {
public:

    enum event_type 
        {
        none,
        keyup,
        keydown
        };

    static void init()
        {
        Pin_::modeInput();
        // aktivate pullup
        Pin_::set();
        previous_ = !Pin_::read();
        changed_ = Timer_::millis();
        duration_ = 0;
        }

    static event_type read()
        {
        const typename Timer_::time_res_t now = Timer_::millis();
        // The button is active low
        const bool pressed = !Pin_::read();

        // If the switch changed, due to noise or pressing...
        if (pressed != previous_) 
            {
            // reset the debouncing timer
            previous_ = pressed;
            const typename Timer_::time_res_t delta = now - changed_;
            changed_ = now;
    
            if (delta > debounce_) 
                {
                if (pressed)
                    {
                    duration_ = now;
                    return keydown;
                    }
            
                duration_ = now - duration_;
                return keyup;
                }
            }
        return none;
        }

    // duration is only valid after a keyup event
    static typename Timer_::time_res_t duration() { return duration_; }

private:
    static bool previous_;
    static typename Timer_::time_res_t changed_;
    static typename Timer_::time_res_t duration_;
};

template<class Timer_, class Pin_, int debounce_>
bool PushButton<Timer_, Pin_, debounce_>::previous_ = false;

template<class Timer_, class Pin_, int debounce_>
typename Timer_::time_res_t PushButton<Timer_, Pin_, debounce_>::changed_ = 0;

template<class Timer_, class Pin_, int debounce_>
typename Timer_::time_res_t PushButton<Timer_, Pin_, debounce_>::duration_ = 0;


#endif
