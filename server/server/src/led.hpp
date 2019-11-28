#ifndef _LED_H
#define _LED_H

#include <Arduino.h>

class Led {
    public:
    bool IsLit();
    void Toggle();
    void Bind(int);
    void SetState(int);
    
    private:
    int _pin;
    int _state;
};

#endif