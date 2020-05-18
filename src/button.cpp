
#include "button.h"
#include <Arduino.h>


button::button(uint16_t pin){
    button::pin = pin;
    defaultState = false;
}

button::button(uint16_t pin, bool defaultState){
    button::pin = pin;
    button::defaultState = defaultState;
}


void button::init(){
    pinMode(pin, INPUT);
}

bool button::getState(){
    return state;
}

void button::check(){
    bool current = digitalRead(button::pin) != defaultState;
    if(state != current){
        if(current){
            pressCount++;
            available_ = true;
        }
        state = current;
    }
}

bool  button::available(){
    return available_;
}

int  button::getPress(){
    available_ = false;
    int count = pressCount;
    pressCount = 0;
    return count;
}

bool button::bePress(){
    if(pressCount){
        pressCount--;
        return true;
    }
    return false;
}