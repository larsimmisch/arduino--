// ringbuffer.h
// Author: Markus Redeker

// small changes for arduino-- by Lars Immisch <lars@ibp.de>

#ifndef ARDUINO_MINUS_MINUS_RINGBUFFER_H
#define ARDUINO_MINUS_MINUS_RINGBUFFER_H

// Usage:

// _Ringbuffer<...> r;
// r.push(new_element);
// oldest_element = r.front(); r.pop();

template<typename ET_, int S_, typename ST_=byte>
class _Ringbuffer
    {
public:
	typedef ET_ value_type;
	typedef ST_ size_type;

	_Ringbuffer()
        { 
		clear(); 
        }

	~_Ringbuffer() {}

	size_type size()     const { return _size; }
	size_type max_size() const { return S_; }

	bool empty() const	{ return _size == 0; }
	bool full()  const	{ return _size == S_; }

	value_type& front() { return _buffer[_front]; }
	value_type& back() { return _buffer[_back]; }

	void clear() 
        {
		_size = 0;
		_front = 0;
		_back  = S_ - 1;
        }

	void push()	
        {
		_back = (_back + 1) % S_;
		if( size() == S_ )
			_front = (_front + 1) % S_;
		else
			_size++;
        }

	void push(const value_type& x) 
        {
		push();
		back() = x;
        }

	void pop() 
        {
		if( _size > 0  ) 
            {
			_size--;
			_front = (_front + 1) % S_;
            }
        }
    
	void back_erase(const size_type n) 
        {
		if( n >= _size )
			clear();
		else 
            {
            _size -= n;
            _back = (_front + _size - 1) % S_;
            }
        }

	void front_erase(const size_type n) 
        {
		if( n >= _size )
			clear();
		else 
            {
			_size -= n;
			_front = (_front + n) % S_;
            }
        }

protected:

	value_type _buffer[S_];

	volatile size_type _size;
	volatile size_type _front;
	volatile size_type _back;
};

#endif // ARDUINO_MINUS_MINUS_RINGBUFFER_H
