#if !defined(MOTOR_H)
#define MOTOR_H

#include <Arduino.h>

#define MOVE    2
#define STOP    1
#define DISABLE 0



class motor
{
private:
    uint8_t   pin_dir;
    uint8_t   pin_step;
    uint8_t   pin_en;

    uint16_t   skip_iterations;
    uint16_t   skip_iterations_high;

    uint16_t  counter;
    uint16_t  speed;
    int16_t   steps;

    uint32_t  timerFreq;
    
    bool      direction;
    bool      invertDirection;
public:
    motor(uint32_t  timerFreq, bool invertDirection, uint8_t pin_dir, uint8_t pin_step);
    motor(uint32_t  timerFreq, bool invertDirection, uint8_t pin_dir, uint8_t pin_step, uint8_t pin_en);
    
    void interrupt();
    void init();
    
    void move(int16_t setps);
    void eneible();
    void diseible();
    void setSpeed(uint16_t speed);
    void incSpeed(int16_t speed);
    
    uint16_t getSpeed(){return speed;}

};



#endif // MOTOR_H
