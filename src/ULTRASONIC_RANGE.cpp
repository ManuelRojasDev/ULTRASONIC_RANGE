#include "Arduino.h"
#include "ULTRASONIC_RANGE.h"

void ULTRASONIC_RANGE::pin_ini(){ // initialize as input or output
	
	for(int i = 0; i < number_of_sensors; i++){
		pinMode(trigger_pins[i], OUTPUT);
		pinMode(echo_pins[i], INPUT);
	}
	
}

ULTRASONIC_RANGE::ULTRASONIC_RANGE(uint8_t trigger_pin_, uint8_t echo_pin_, uint16_t trigger_pulse_, unsigned long timeout_){// to be used only with one sensor

	trigger_pins[0] = trigger_pin_;
	echo_pins[0] = echo_pin_;
	timeout = timeout_;
	
	number_of_sensors = 1;
	
	pin_ini();
}

ULTRASONIC_RANGE::ULTRASONIC_RANGE(uint8_t *trigger_pins_, uint8_t *echo_pins_, uint8_t N_sensors, uint16_t trigger_pulse_, unsigned long timeout_){// to be used only with one sensor
	number_of_sensors = N_sensors;
	
	for(int i = 0; i < number_of_sensors; i++){
		trigger_pins[i] = *trigger_pins_++;
		echo_pins[i] = *echo_pins_++;
	}
	
	timeout = timeout_;
	trigger_pulse = trigger_pulse_;
	pin_ini();
	
}


bool ULTRASONIC_RANGE::TOF(){
	
	
	
	unsigned long time_stamp;// used to save the time before entering a long for loop;
	

	for(int i = 0; i < number_of_sensors; i++){
		digitalWrite(trigger_pins[i], HIGH);
	}
	
	delayMicroseconds(trigger_pulse);
	
		for(uint8_t i = 0; i < number_of_sensors; i++){
		digitalWrite(trigger_pins[i], LOW);
	}
	
	timeout_timer = micros();
	
	
	while(active){
		
		time_stamp = micros();
		// read echo pin and start timing if read high
		for(uint8_t i = 0; i < number_of_sensors; i++){
			
			if(states[i] == 0){
				
				if(digitalRead(echo_pins[i]) == HIGH){
					timers[i] = time_stamp;
					states[i] = 1;
					
				}
					
				
			}
			
		}
		
		time_stamp = micros();
		// read echo pin and calculate time of flight if read low
		for(uint8_t i = 0; i < number_of_sensors; i++){
			
			if(states[i] == 1){
				
				if(digitalRead(echo_pins[i]) == LOW){
					time_of_flight[i] = time_stamp - timers[i];
					if( number_of_sensors - 1 == i){/// set to exit if this is the last sensor
						active = false;
						TOF_ = true;/// reading successful 
					}
					
					states[i] = 2;
				}
			}
		}
		
		
		if( micros() - timeout_timer > 1000000){ /// exit the loop if timed out;
			active = false;
			
			for(uint8_t i = 0; i < number_of_sensors; i++){ /// write success if sensor was read correctly
				if(states[i] == 2){
					success[i] = true;
				}else{
					success[i] = true;
				}
			}
			
		}
		
		

		
		
		
		
	}
	
	
	for(int i = 0; i < number_of_sensors; i++){
		states[i] = 0;
	}
	
    active = true;
	
	return TOF_;
}


float ULTRASONIC_RANGE::update(){// will give out the reading of the first sensor

	
	if(TOF() == true){
		
	for(int i = 0; i < number_of_sensors; i++){
		if(filter == true){
			distance[i] = distance[i] * 0.8 + time_of_flight[i] * 343.00 / 20000.00 * 0.2;
		}else{
			distance[i] = time_of_flight[i] * 343.00 / 20000.00;
		}
	}
	}
	TOF_ = false;
	
	

return distance[0];

}