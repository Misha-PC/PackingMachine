#ifndef PINS_H
#define PINS_H
/*  BTN_SHEELD

* 3
* 4             ___________     ___________
* 5            *|         |    *|         |
* 6            *| 4       |    *| 3       |
* 7            *|_________|    *|_________|
    
    ___________     ___________
    |         |*    |         |*      gnd*
    |       5 |*    |       6 |*      vcc*
    |_________|*    |_________|*
    
                                      _______
                                      |_*_*_|
                                        7

*/

#define PIN_BTN_RIGHT 6
#define PIN_BTN_LEFT  5
#define PIN_BTN_HOME  4
#define PIN_BTN_AUTO  3
#define PIN_ENDSTOP   7

#define PIN_DIR_M1    52
#define PIN_STEP_M1   50

#define PIN_DIR_M0    34
#define PIN_STEP_M0   32

#define PIN_LED       13

#endif