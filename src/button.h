#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class button
{
protected:
    uint16_t pin;
    int pressCount;
    bool state, available_, defaultState;
public:
    button(uint16_t pin);
    button(uint16_t pin, bool defaultState);
    void check(void);
    void init(void);
    bool getState(void);
    bool available(void);
    bool bePress(void);
    int  getPress(void);
    
};



#endif // BUTTON_H
