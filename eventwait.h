// -*- mode: c++; indent-tabs-mode: nil; -*-

#ifndef ARDUINO_MINUS_MINUS_EVWAIT_H
#define ARDUINO_MINUS_MINUS_EVWAIT_H

// Wait for events. Clock_ must be a Clock class, Cont_ is a container
// and must implement empty
template<class Clock_, class Cont_>
class _EventWait : public Cont_
    {
public:

    void wait_event()
        {
        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_enable();
#ifdef sleep_bod_disable
        sleep_bod_disable();
#endif
        while (Cont_::empty())
            {
            sei();
            sleep_cpu();
            }

        sei();
        sleep_disable();
        }

    void wait_event(typename Clock_::time_res_t ms)
        {
        const typename Clock_::timeres_t start = Clock_::millis();

        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_enable();
#ifdef sleep_bod_disable
        sleep_bod_disable();
#endif
        while (Cont_::empty() && Clock_::millis() - start <= ms)
            {
            sei();
            sleep_cpu();
            }

        sei();
        sleep_disable();
        }
    };

#endif

