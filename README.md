# arduino_ir_lifesize_remote
LifeSize remote buttons decoded for use in Arduino

# Setup

* An IR receiver similar to https://arduino-info.wikispaces.com/IR-RemoteControl

# Decoding

* Used https://github.com/z3t0/Arduino-IRremote to detect pulses and their widths
* Used a digital scope to view the pulses and measure their timings

Here is the pulses when zero button is pressed.

![Zero button pulses](/Button-zero-pulses.PNG?raw=true)

Notice there are 36 pulses
* Start indicator pulses: low (2600-2800) ms, high (2300-2600) ms (2 pulses)
* Stop pulse: low (1200-1600) ms (35th pulse)
* There are 32 pulses between pulse 3 to 35
* Each pair of pulses forms a bit => 16 bit value
* Bit 1: mid-low (1200-1600) ms -> long-high (2500) ms
* Bit 0: mid-low (1200-1600) ms -> short-high (800-900) ms

For example for button zero as shown above

start 1001,1000,1100,0001 stop

I also found that each button sends 2 different codes

The codes are stored as hex in lifesize-button.h. For example button zero is 0x98C1.




