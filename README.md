# Power rate and AC #
For DC it is much easier to control power using PWM where we use mosfets and can close or open it anytime.

Howerver, for AC we have to deal with triacs. Triac also, has a gate to control it, but if triac was turned ON, 
it can not be turned OFF until the AC voltage goes down to 0 volt.
If we consider the AC electricity with 220 V and 50 Hz, there are 50 full periods of sine and 100 half periods (50 voltage positive 50 voltage negative).

One of way to manage power rate is Phase Shift.


# Installation #
Create a new folder called "BresenhamTriacDriver" under the folder named "libraries" in your Arduino sketchbook folder.
Create the folder "libraries" in case it does not exist yet. Place all the files in the "BresenhamTriacDriver" folder.

# Usage #
To use the library in your own sketch, select it from *Sketch > Import Library*.

-------------------------------------------------------------------------------------------------------------------