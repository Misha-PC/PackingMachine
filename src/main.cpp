
#include <Arduino.h>
#include "button.h"
#include "pins.h"
#include "interrupt_controller.h"


#define PIN_LED 13

bool state, active;
bool direction;
int  steps = 200, high_time;
int  speed, counter;


ISR(TIMER5_A){

  if(active){
    counter++;
    if(counter >= speed){
      digitalWrite(PIN_STEP_M0, state);
      state = !state;
      counter = 0;
    }
    // steps--;
  }
  
}

button btn_change_direction(5);
button btn_start(6);

button btn_speed_up(4);
button btn_speed_down(3);

button endstop(7, true);

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

  Timer4.setFrequency(100);
  Timer4.enableISR();

  Timer5.setFrequency(10000);
  Timer5.enableISR();
}


void loop() {
  if(endstop.available()){
    active = false;
    Serial.println("ENDSTOP");
    endstop.getPress();
    endstop.bePress(); 
    direction = !direction;
    digitalWrite(PIN_DIR_M0, direction);
  }

  

  if(btn_change_direction.available()){
    btn_change_direction.getPress();
    direction = !direction;
    digitalWrite(PIN_DIR_M0, direction);
  }

  if(btn_start.available()){
    btn_start.getPress();
    active = !active;
    // direction = !direction;
    // digitalWrite(PIN_DIR_M0, direction);
    Serial.println(active? "START":"STOP");    
  }

  if(btn_speed_down.available()){
    speed -= btn_speed_down.getPress()*100;
    Serial.println(speed);
  }

  if(btn_speed_up.available()){
    speed += btn_speed_up.getPress()*100;
    Serial.println(speed);
  }
  

}
