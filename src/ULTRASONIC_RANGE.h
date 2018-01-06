#ifndef ULTRASONIC_RANGE_h
#define ULTRASONIC_RANGE_h

/* This library is usefull when using more than one range sensor that you want to read from simultaniously, you can also use it with just one sensor;
//ULTRASONIC_RANGE(uint8_t *trigger_pins, uint8_t *echo_pins, uint8_t N_sensors, uint16_t trigger_pulse, unsigned long timeout); /// to be used with an array of ultrasonic range sensors
//ULTRASONIC_RANGE(uint8_t trigger_pin, uint8_t echo_pins, uint16_t trigger_pulse, unsigned long timeout);// to be used only with one sensor

MR NODOOD 2018 5 jan follow me on github for any questions or updates; github.com/nodood
*/

#ifndef Max_sensors // define the max number of sensors that will be used, by default its 5;
	#define Max_sensors 5
#endif

#include "Arduino.h"

class ULTRASONIC_RANGE
{

public:

	ULTRASONIC_RANGE(uint8_t *trigger_pins, uint8_t *echo_pins, uint8_t N_sensors, uint16_t trigger_pulse, unsigned long timeout); /// to be used with an array of ultrasonic range sensors
	ULTRASONIC_RANGE(uint8_t trigger_pin, uint8_t echo_pins, uint16_t trigger_pulse, unsigned long timeout);// to be used only with one sensor
	
	
	
	float update();// will give out the reading of the first sensor
	bool TOF();// time of flight function this is the main sensor function

unsigned long time_of_flight[Max_sensors];

	float sound_speed = 343;// speed of sound in meters per second;
	float distance[Max_sensors]; // store the calculated distance
	bool filter = false;// activate filter // experimental
	unsigned long timeout = 15000;// sense timeout in micros



private:
	
	
	uint8_t number_of_sensors = 1;
	uint8_t trigger_pins[Max_sensors];
	uint8_t echo_pins[Max_sensors];
	
	unsigned long trigger_pulse = 10;// trigger pulse in micros
	unsigned long timers[Max_sensors];// time of flight timers;
	unsigned long timeout_timer;// timeout timer
	bool success[Max_sensors];
	
	uint8_t states[Max_sensors];
	uint8_t sum_state;
	
	bool active = true;// active after the trigger has been triggered until the echo has been captured or timeout
	void pin_ini(); //initialize pins
	
	bool TOF_; // if reading was success, else use old value
	
	

};
#endif




