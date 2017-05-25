# Power rate and AC #
For DC it is much easier to control power using PWM where we use mosfets and can close or open it anytime.

Howerver, for AC we have to deal with triacs. Triac also, has a gate to control it, but if triac was turned ON, 
it can not be turned OFF until the AC voltage goes down to 0 volt.
If we consider the AC electricity with 220 V and 50 Hz, there are 50 full periods of sine and 100 half periods (50 voltage positive 50 voltage negative).

One of possible way to manage power rate is Phase Shift:
![Phase Shift](https://raw.githubusercontent.com/biletnikov/bresenham-triac-driver/master/Images/Phase-Shift.png)

to make it work you need AD zero cross detector and turn ON triac for the necessary shift of phase, but before its end.
It works fine, but the big drawback is lots of Electromagnetic interference (EMI), and the things go bad when you need to commutate big power, like 4 kWatt. 
You will get lots of EMI and triacs will be in the stressful mode.

It is much better to turn on the triac when the voltage is low (near to 0 volt) and the another way is to turn on triac only for certain half of periods:
![Bresehnham](https://raw.githubusercontent.com/biletnikov/bresenham-triac-driver/master/Images/Bresenham.png)
In this case, no problems with EMI.
Howerver, how to rate the power in more precize way? For example, you need power rate = 40% , do you need to turn the triac on only for first 40 half periods ?
To solve this issue in more precise way we can use Bresenham algorithm, which can help us to spread the power for the certain period.

Lets see example for 50 Hz -> 100 half periods,  . - triac is off,  # - triac is on:

![Bresenham Algorithm](https://raw.githubusercontent.com/biletnikov/bresenham-triac-driver/master/BresenhamAlgorithmExample.txt)

Also, for this method we need zero cross detector and triac must be managed with MOC3041 (or similar IC) with zero cross detection inside.
As alternative, Solid State Relay can be used as well (with zero cross detection inside), like Fotek SSR-40 DA.

But you can not use this approach for light dimming which needs more higher frequency.
For 50 Hz AC, the triac can be on from 0 to 100 times per second. For resistive load (heaters) it is very normal, but bulbs will blinking.

# Zero Cross Detector #
The detector is necessary for processing Bresenham Algorithm. 
[The zero cross detector schematic](Schematic/AC-Zero-Cross-Detector.png)

And oscillogram of this circuit:
![Zero Cross Detector Oscillogram](https://raw.githubusercontent.com/biletnikov/bresenham-triac-driver/master/Images/ZeroCrossDetector_Oscillogram.png)

The peak of the pulse, when the volotage equals to 0 Volts.

![Zero Cross Detector Oscillogram Explanation](https://raw.githubusercontent.com/biletnikov/bresenham-triac-driver/master/Images/ZeroCrossDetector_Oscillogram_explanation.png)

# Installation #
Create a new folder called "BresenhamTriacDriver" under the folder named "libraries" in your Arduino sketchbook folder.
Create the folder "libraries" in case it does not exist yet. Place all the files in the "BresenhamTriacDriver" folder.

# Usage #
To use the library in your own sketch, select it from *Sketch > Import Library*.

# Demo sketch #
TestScketch.ino


-------------------------------------------------------------------------------------------------------------------