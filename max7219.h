/* 
 Driver for the MAX7219 matrix multiplexer.
 Multiple cascaded devices are supported.


 Code History:
 --------------

The orginal code was written for the Wiring board by:
 * Nicholas Zambetti and Dave Mellis /Interaction Design Institute Ivrea /Dec 2004
 * http://www.potemkin.org/uploads/Wiring/MAX7219.txt

First modification by:
 * Marcus Hannerstig/  K3, malmø høgskola /2006
 * http://www.xlab.se | http://arduino.berlios.de

Next modifications by:
 * tomek ness /FH-Potsdam / Feb 2007
 * http://design.fh-potsdam.de/ 
 * @acknowledgements: eric f. 

Version for arduino-- by:
 * Lars Immisch <lars@ibp.de>

 --

 This example sets the same pattern on all cascaded devices:

  typedef class _Max7219<Arduino::D4, Arduino::D5, Arduino::D6> Max7219;

  Max7219::init();

  Max7219::set(Max7219::ROW0, 1);   //  + - - - - - - -
  Max7219::set(Max7219::ROW1, 3);   //  + + - - - - - -
  Max7219::set(Max7219::ROW2, 7);   //  + + + - - - - -
  Max7219::set(Max7219::ROW3, 15);  //  + + + + - - - -
  Max7219::set(Max7219::ROW4, 31);  //  + + + + + - - -
  Max7219::set(Max7219::ROW5, 63);  //  + + + + + + - -
  Max7219::set(Max7219::ROW6, 127); //  + + + + + + + -
  Max7219::set(Max7219::ROW7, 255); //  + + + + + + + +

*/

template <class CLOCK_, class DATA_, class CS_, byte max_=1>
class _Max7219
    {
public:

    // max7219 registers
    static const byte NOOP        = 0x00;
    static const byte ROW0        = 0x01;
    static const byte ROW1        = 0x02;
    static const byte ROW2        = 0x03;
    static const byte ROW3        = 0x04;
    static const byte ROW4        = 0x05;
    static const byte ROW5        = 0x06;
    static const byte ROW6        = 0x07;
    static const byte ROW7        = 0x08;
    static const byte DECODE_MODE = 0x09;
    static const byte INTENSITY   = 0x0a;
    static const byte SCANLIMIT   = 0x0b;
    static const byte SHUTDOWN    = 0x0c;
    static const byte DISPLAYTEST = 0x0f;

    static void init(byte intensity = 0x7f)
        {
        CLOCK_::modeOutput();
        DATA_::modeOutput();
        CS_::modeOutput();

        CLOCK_::set();

        // initialize all devices
        set(SCANLIMIT, 0x07);      
        set(DECODE_MODE, 0x00);  // using an led matrix (not digits)
        set(SHUTDOWN, 0x01);    // not in shutdown mode
        set(DISPLAYTEST, 0x00); // no display test

        for (byte e = ROW0; e <= ROW7; ++e) 
            {
            set(e, 0); // turn all LEDs off 
            }
        set(INTENSITY, intensity & 0x0f);    
        }

    // This is the max7219 variant of SPI. 
    // We can't do it in hardware, so we bit-bang it 
    static void transmit(byte data)
        {
        for (byte i = 8; i > 0; --i) 
            {
            byte mask = 0x01 << (i - 1);
            CLOCK_::clear(); // tick
            if (data & mask)
                DATA_::set(); // send 1
            else
                DATA_::clear(); // send 0
            CLOCK_::set(); // tock
            }
        }

    /// set a register for all cascaded devices 
    static void set(byte reg, byte val) 
        {
        CS_::clear();       // begin     
        for (byte c = 0; c < max_; c++) 
            {
            transmit(reg); // specify register
            transmit(val); // ((data & 0x01) * 256) + data >> 1); // put data
            }
        CS_::clear(); // and load da shit
        CS_::set(); 
        }

    /// set a register on device <nr>
    static void set(byte nr, byte reg, byte val) 
        {
        int c = 0;
        CS_::clear();

        for (c = max_; c > nr; c--) 
            {
            transmit(NOOP);
            transmit(0);
            }

        transmit(reg); // specify register
        transmit(val); // send value

        for (c = nr-1; c >= 1; c--) 
            {
            transmit(NOOP);
            transmit(0);
            }

        CS_::clear(); // and load da shit
        CS_::set(); 
        }
    };
