#include "motor.h"


#include <Arduino.h>



    
motor::motor(uint32_t  timerFreq, bool invertDirection, uint8_t pin_dir, uint8_t pin_step){
    motor::invertDirection = invertDirection;
    motor::timerFreq       = timerFreq;
    motor::pin_dir         = pin_dir;
    motor::pin_step        = pin_step;
}

motor::motor(uint32_t  timerFreq, bool invertDirection, uint8_t pin_dir, uint8_t pin_step, uint8_t pin_en){
    motor::invertDirection = invertDirection;
    motor::timerFreq       = timerFreq;
    motor::pin_dir         = pin_dir;
    motor::pin_step        = pin_step;
    motor::pin_en          = pin_en;
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
        if(counter == skip_iterations_high)
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

    if(invertDirection)
        digitalWrite(pin_dir, steps > 0);
    else
        digitalWrite(pin_dir, steps < 0);

    motor::steps += abs(steps);
}

void motor::setSpeed(uint16_t speed /*steps per second*/){
    motor::speed         = speed;
    skip_iterations      = timerFreq / speed;
    skip_iterations_high = skip_iterations/100+1;

    Serial.print(speed);
    Serial.print("\t:\t");
    Serial.print(skip_iterations);
    Serial.print("\t:\t");
    Serial.println(skip_iterations_high);
    /*
    *   x = freq
    *   y = speed 
    * 
    *         1000000 / x               //timer period
    *    ------------------- = x/y
    *         1000000 / y               //need period

    */

}

void motor::incSpeed(int16_t speed){
    motor::setSpeed(motor::speed + speed);
}