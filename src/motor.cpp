#include "motor.h"


#include <Arduino.h>



    
motor::motor(uint32_t  timerFreq, uint8_t pin_dir, uint8_t pin_step){
    motor::timerFreq = timerFreq;
    motor::pin_dir   = pin_dir;
    motor::pin_step  = pin_step;
}

motor::motor(uint32_t  timerFreq, uint8_t pin_dir, uint8_t pin_step, uint8_t pin_en){
    motor::timerFreq = timerFreq;
    motor::pin_dir   = pin_dir;
    motor::pin_step  = pin_step;
    motor::pin_en    = pin_en;
}

void motor::init(){
    pinMode(pin_step, OUTPUT);
    pinMode(pin_dir,  OUTPUT);
    if(pin_en)
        pinMode(pin_en,   OUTPUT);
}



void motor::interrupt(){
    if(steps){
        counter++;
        if(counter == skip_iterations+1)
            digitalWrite(pin_step, HIGH);
        else if(counter == skip_iterations){
            digitalWrite(pin_step, LOW);
            steps -= 1;
            counter = 0;
        }
    }
}


void motor::move(int16_t steps){    

    if(steps == 0)
        return;

#ifdef INVERT_DIR_M0
    digitalWrite(pin_dir, steps > 0);
#else
    digitalWrite(pin_dir, steps < 0);
#endif

    motor::steps = abs(steps);
}

void motor::setSpeed(uint16_t speed){
    motor::speed    = speed;
    skip_iterations;
}