
#include <Arduino.h>
#include "button.h"
#include "pins.h"
#include "interrupt_controller.h"
#include "motor.h"
#include "configuration.h"





bool state, active;
bool direction;
int  steps = 200, high_time;
long int  speed, counter;




button btn_change_direction(5);
button btn_start(6);

button btn_speed_up(4);
button btn_speed_down(3);

button endstop(7, true);

motor m0(MOTOR_TIMER_FREQ, M0_IVERTION, PIN_DIR_M0, PIN_STEP_M0);
motor m1(MOTOR_TIMER_FREQ, M1_IVERTION, PIN_DIR_M1, PIN_STEP_M1);

ISR(TIMER5_A){
  m0.interrupt();
  m1.interrupt();
}


ISR(TIMER4_A){
  btn_speed_up.check();
  btn_speed_down.check();
  btn_change_direction.check();
  btn_start.check();
  endstop.check();
}


void setup() {
  btn_change_direction.init();
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_STEP_M0, OUTPUT);
  pinMode(PIN_DIR_M0, OUTPUT);
  Serial.begin(9600);

  m0.init();
  m1.init();

  m0.setSpeed(1600);
  m1.setSpeed(400);

  delay(5);

  Timer4.setFrequency(100);
  Timer4.enableISR();

  Timer5.setFrequency(MOTOR_TIMER_FREQ);
  Timer5.enableISR();
}


void loop() {
  // if(endstop.available()){
  //   active = false;
  //   Serial.println("ENDSTOP");
  //   endstop.getPress();
  //   direction = !direction;
  // }

  

  if(btn_change_direction.available()){
    btn_change_direction.getPress();
    m0.move(-200*M0_MICROSTEPS*4);
    m1.move(-200*M0_MICROSTEPS);
  }

  if(btn_start.available()){
    btn_start.getPress();
    m0.move(200*M0_MICROSTEPS*4);
    m1.move(200*M0_MICROSTEPS);
  }

  if(btn_speed_down.available()){
    int s = -btn_speed_down.getPress()*100;

    m0.incSpeed(s);
    m1.incSpeed(s/4);
  }


  if(btn_speed_up.available()){
    int s = btn_speed_up.getPress()*100;

    m0.incSpeed(s);
    m1.incSpeed(s/4);

  }
  

}
