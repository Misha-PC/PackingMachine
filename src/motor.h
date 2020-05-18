#if !defined(MOTOR_H)
#define MOTOR_H

#include <Arduino.h>

class motor
{
private:
    uint8_t   pin_dir;
    uint8_t   pin_step;
    uint8_t   pin_en;

    uint16_t   skip_iterations;

    uint16_t  counter;
    uint16_t  speed;
    int16_t   steps;

    uint32_t  timerFreq;
    
    bool      direction;
public:
    motor(uint32_t  timerFreq, uint8_t pin_dir, uint8_t pin_step, uint8_t pin_en);
    motor(uint32_t  timerFreq, uint8_t pin_dir, uint8_t pin_step);
    
    void interrupt();
    void init();
    
    void move(int16_t setps);
    void eneible();
    void diseible();
    void setSpeed(uint16_t speed);
    void incSpeed();
    
    uint16_t getSpeed();

};



#endif // MOTOR_H
