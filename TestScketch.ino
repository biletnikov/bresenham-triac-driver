#include <BresenhamTriacDriver.h>

#define PIN_POT A1 // POT , any analog pin can be set
#define PIN_AC_ZERO_INT 8 // ac zero cross interrupts
#define PIN_SSR 9 // solid state relay

#define HALF_PERIODS_PER_CYCLE 100 // with 50 Hz AC , each cycle will run in 1 second with 100 possible half periods

BresenhamTriacDriver * triacDriver;

void setup() {
  // init driver
  triacDriver = new BresenhamTriacDriver(HALF_PERIODS_PER_CYCLE, PIN_SSR, PIN_AC_ZERO_INT, HIGH);  
}

void loop() {

  // read potentiometer to get new power rate value
  int power_value = analogRead(PIN_POT);
  
  // power rate must be in the range 0 .. HALF_PERIODS_PER_CYCLE 
  power_value = map(power_value,0,1023,0,HALF_PERIODS_PER_CYCLE);
  triacDriver->set_power_rate(power_value);

  // run main dirver routine
  triacDriver->check_ac();   
}
