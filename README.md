# arduino_ir_lifesize_remote
LifeSize remote buttons decoded for use in Arduino

# Setup

* An IR receiver similar to https://arduino-info.wikispaces.com/IR-RemoteControl

# Decoding

* Used https://github.com/z3t0/Arduino-IRremote to detect pulse widths
* Used a digital scope to view the pulses and measure their timing

For example, here is the pulses when zero button is pressed.

![Zero button pulses](/Button-zero-pulses.PNG?raw=true)

Notice there are 36 pulses
* Start indicator pulses: low (2600-2700) ms, high (2300-2400) ms (2 pulses)
* Stop pulse: low (1200-1400) ms (35th pulse)
* There are 32 pulses between pulse 3 to 35
* Each pair of pulses forms a bit => 16 bit value
* Bit 1: mid-low (1200-1400) ms -> long-high (2500) ms
* Bit 0: mid-low (1200-1400) ms -> short-high (800-900) ms

For example for button zero as shown above

start 1001,1000,1100,0010 stop


I also found that each button sends 2 different codes


