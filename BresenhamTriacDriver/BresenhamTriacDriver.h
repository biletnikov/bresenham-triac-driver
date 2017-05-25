/**
 * BresenhamTriacDriver.h - Library for driving triacs and solid state relays
 * with Bresenham algorithm. It is necessary that triac or solid state relay is used with zero cross detector. 
 * So, for triac you can use IC like moc3041 or choose solid state relay with zero cross detector inside.
 * This library is excellent for resistitve loads such as heaters for big loads like 2kwt, 4kwt and is not applicable for light dimming, becuase of blinking.
 * The benefit of the light is the power regulation along with zero cross detector which prevents EMI and makes more safr
 */


#ifndef BresenhamTriacDriver_h
#define BresenhamTriacDriver_h


#include "Arduino.h"

class BresenhamTriacDriver
{

  public:
    BresenhamTriacDriver(
	int half_periods_in_cycle, // if you get 50 Hz AC electricity, it has 100 half periods inside per second. If you set here 100, 1 cycle = 1 sec, if you set 50 , than 1 cycle = 0.5 sec
	int triac_pin, // an output pin to control triac, usually it connects to optocoupler inside MOC3041 or similar IC
	int zero_cross_detector_pin, // cross detector pin
	int zero_cross_level // when to trigger: HIGH on rising edge,  LOW on falling edge. If you use the zero detector like in the attached schematic, this must be HIGH
	);
	// returns 1 if ac zero cross detected, otherwise 0
    int check_ac();
	// set power rate, the value must be from 0 to half_periods_in_cycle value (max)
    void set_power_rate(int power_rate);

  private:
    int _triac_pin;
    int _zero_cross_detector_pin;
    int _zero_cross_level;
    int _half_periods_in_cycle;
    int _power_rate;
};

#endif
