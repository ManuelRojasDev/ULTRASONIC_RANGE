#include "ULTRASONIC_RANGE.h"

/* This library is usefull when using more than one range sensor that you want to read from simultaniously, you can also use it with just one sensor;
//ULTRASONIC_RANGE(uint8_t *trigger_pins, uint8_t *echo_pins, uint8_t N_sensors, uint16_t trigger_pulse, unsigned long timeout); /// to be used with an array of ultrasonic range sensors
//ULTRASONIC_RANGE(uint8_t trigger_pin, uint8_t echo_pins, uint16_t trigger_pulse, unsigned long timeout);// to be used only with one sensor

MR NODOOD 2018 follow me on github for any questions or updates; github.com/nodood
*/

uint8_t trigger_pins[2] = {8, 9};
uint8_t echo_pins[2] = {10, 11};

ULTRASONIC_RANGE range(trigger_pins, echo_pins, 2, 10, 15000);/// trigger, echo, number of sensors, trigger pulse length, timeout ( in micros ) about 15 millis determined by knowing the max range that the sensor can sense;



void setup() {
  Serial.begin(9600);


}

void loop() {
    range.update();
    Serial.println(String(range.distance[0])+","+String(range.distance[1]));

    
    delay(20);// note a higher refresh rate more than this can cause trouble readings
}
