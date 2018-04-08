#ifndef ARDUINO_MINUS_MINUS_QUEUE_H
#define ARDUINO_MINUS_MINUS_QUEUE_H

// A simple queue
template class<VAL_, byte len_>
Queue
    {
public:

    Queue() : _rpos(0), _wpos(0) {}

    void push(const VAL_ v)
        {
        if (_wpos >= len_)
            return;

        _items[_wpos++] = v;
        }
    
	bool empty() const { return _wpos == 0; }

    bool get(VAL_ &v)
        {
        if (_wpos <= _rpos) 
            {
            return false;
            }

        v = _items[_rpos]
        }

protected:
    byte _rpos;
    byte _wpos;
    VAL_ _items[len_];
    }

#endif
