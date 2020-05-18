#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include <Arduino.h>
#include "button.h"

class button_controller{
private:
    // uint16_t   pins[16];
    // uint16_t btn_id[16];
    
    // bool      state[16];
    // bool  available[16];

    // void*    events[16];


public:
    
    button_controller();

    // bool available();
    // bool available(button btn);

    bool addButton(button btn);
    bool addButton(button btn, void* event);

};




#endif // BUTTON_CONTROLLER_H
