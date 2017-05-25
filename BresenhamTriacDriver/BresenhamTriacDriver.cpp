#include "Arduino.h"
#include "BresenhamTriacDriver.h"


// this class implements Bresenham algorithm
class Bresenham
{
  private:
  int size = 0;
  int value = 0;
  int error = 0;
  int stepNumber = 0;
  int bres_counter;

  public:
  Bresenham(int set_size)
  {
   size = set_size;
   bres_counter = size;
  }
  
  void set_value(int val) {
        stepNumber = 0;
        value = val;
        error = size/2;
  }

  int get_next() {
        boolean result;
        error -= value;
        if ( error < 0 ) {
            error += size;
            result = true;
        } else {
            result = false;
        }
        if ( ++stepNumber >= size) {
            stepNumber = 0;
            error = size/2;
        }
        return result;
   } 
   
   // returns 0 if the counter is reset
   int cycle() {
	   int current_value = bres_counter;
	   
	   if (bres_counter == 0) {
		   bres_counter = size;		   
	   }
	   bres_counter--;
	   
	   return current_value;
   }
};

Bresenham * bresenham;
int prev_ac_int_state;


// driver implementation
BresenhamTriacDriver::BresenhamTriacDriver(int half_periods_in_cycle, int triac_pin, int zero_cross_detector_pin, int zero_cross_level)
{
  bresenham = new Bresenham(half_periods_in_cycle);
  
  pinMode(zero_cross_detector_pin, INPUT);
  pinMode(triac_pin, OUTPUT);
  
  _triac_pin = triac_pin;
  _zero_cross_detector_pin = zero_cross_detector_pin;
  _zero_cross_level = zero_cross_level;
  
  // init AC int state
  prev_ac_int_state = digitalRead(zero_cross_detector_pin);
}

// set power rate value
void BresenhamTriacDriver::set_power_rate(int power_rate)
{
  _power_rate = power_rate;
}

// the main routine, which chekcs ac zero cross detector, runs Bresenham algorithm and turn on/off triac or SSR
int BresenhamTriacDriver::check_ac()
{
    int current_ac_int_state = digitalRead(_zero_cross_detector_pin);
	int zero_cross_detected = 0;
	  // check on new interrupts
	  if (current_ac_int_state != prev_ac_int_state)
	  {
		int cycle_result = bresenham->cycle();
		
		if (cycle_result == 0) {     
			// new  cycle begin, set power rate
		  bresenham->set_value(_power_rate);     
		}
		
		// check cross zero detector on rising or falling edge
		if ((current_ac_int_state == HIGH && _zero_cross_level == HIGH) || ((current_ac_int_state == LOW && _zero_cross_level == LOW)))
		{
		  if (bresenham->get_next()) {
			digitalWrite(_triac_pin, HIGH);
		  } else {
			digitalWrite(_triac_pin, LOW);
		  }      
		  
		  zero_cross_detected = 1;
		}

		prev_ac_int_state = current_ac_int_state;    
	  }
  
  return zero_cross_detected;
}




