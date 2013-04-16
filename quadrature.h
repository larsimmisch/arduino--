/******************************************************************************
 *  quadrature.h - Arduino library for reading quadrature encoders.
 *  Version 0.90
 *  Created by Keith Neufeld, June 29, 2008.
 *
 *  Templatified for use with arduino-- by Lars Immisch
 * 
 *  This work is licensed under the Creative Commons Attribution-Share Alike 
 *  3.0 Unported License. To view a copy of this license, visit
 *  http://creativecommons.org/licenses/by-sa/3.0/ or send a letter to
 *  Creative Commons, 171 Second Street, Suite 300, San Francisco, California,
 *  94105, USA.
 ******************************************************************************/


#ifndef ARDUINO_MINUS_MINUS_QUADRATURE_H
#define ARDUINO_MINUS_MINUS_QUADRATURE_H

// These constants should probably be in the _Quadrature class, but I don't
// trust the compiler to fold multiple template instatiations into one yet 

namespace Quadrature_ {

  static const int Half [4][4] = {
      { 0, -1, 1, 0 },	//  00 -> 10 is CW
      { 1, 0, 0, -1 },	//  01 -> 00 is CW
      { -1, 0, 0, 1 },	//  10 -> 11 is CW
      { 0, 1, -1, 0 }		//  11 -> 01 is CW
  };

  static const int Full [4][4] = {
      { 0, 0, 0, 0 },		//  00 -> 10 is silent CW
      { 1, 0, 0, -1 },	//  01 -> 00 is CW
      { -1, 0, 0, 1 },	//  10 -> 11 is CW
      { 0, 0, 0, 0 }		//  11 -> 01 is silent CW
  };

  static const int NoLimit = -1;
};

template<class Pin1_, class Pin2_, int min_ = Quadrature_::NoLimit, 
         int max_ = Quadrature_::NoLimit>
class _Quadrature
    {
public:

    static void init()
        {
        Pin1_::modeInputPullup();
        Pin2_::modeInputPullup();

        _previous = _readpins();		//  read initial position
        }

	static int position(void) 
        {
        return _position;
        }

	static void position(int pos)
        {
        _position = pos;
        }

    /** This should be called from the clock ISR 
     */
    static int update()
        {
        const int quadbits = _readpins();

        if (quadbits != _previous) 
            {
            int position = _position +
                Quadrature_::Full[_previous][quadbits];

            //  limit to minimum if assigned
            position = (min_ != Quadrature_::NoLimit) 
                ? (min_ > position ? min_ : position) : position;

            //  limit to maximum if assigned
            _position = (max_ != Quadrature_::NoLimit)
                ? (max_ < position ? max_ : position) : position;

            _previous = quadbits;
            }
       
        return quadbits;    
        }

private:

	static int _readpins(void)
        {
        return Pin2_::read() << 1 | Pin1_::read(); 
        }

	volatile static int _position;
	volatile static int _previous;
};

template<class Pin1_, class Pin2_, int min_, int max_>
volatile int _Quadrature<Pin1_, Pin2_, min_, max_>::_position = 0;

template<class Pin1_, class Pin2_, int min_, int max_>
volatile int _Quadrature<Pin1_, Pin2_, min_, max_>::_previous = 0;

#endif // ARDUINO_MINUS_MINUS_QUADRATURE_H
