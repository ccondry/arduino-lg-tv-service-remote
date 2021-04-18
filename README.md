# Arduino LG TV Service Remote
This is an Arduino sketch to send the IR commands to an LG OLED TV to open the
Service Menu, which cannot be opened by the normal remote (at least, not the 
Magic Remote that comes with newer LG OLED TVs.) I'm using this on an LG
`OLED48CXPUB` TV to turn off ASBL (Auto Screen Brightness Leveling), which is only
available in the Service Menu. 

## Requirements
You need an IR LED, an Arudino that is supported by the 
[IRRemote library](https://arduino-irremote.github.io/Arduino-IRremote/), and
you need the IRRemote library itself installed in your Arduino IDE. It' probably
best to have a 100-500 ohm resistor, but you can likely get away with another
one of similar resistance or even with no resistor at all.

## Usage
Upload the sketch to your Arduino, connect the anode (positive) lead of an IR
LED to digital pin 3 of the Arduino, and connect the cathode (negative) lead of
the IR LED to ground via a small resistor. The sketch code will send the
`IN_START` signal, followed by the `0413` digits code that is required by the
password prompt on the TV. Reset or power cycle the Arudino to send the codes
again. 

## Options
#### Resistor
I used a 150-ohm resistor for the IR LED, but I think almost any value under 1k
would probably work. It should even work with no resistor, as the Arduino sketch
is using software PWM to send power to the LED. PWM pulses the power to the IR
LED, and if memory serves, IR LEDs can dissipate a higher current than a
comparable visible-spectrum LED.

#### Arduino Nano
I'm using an Arduino Nano clone from Elegoo, which requires 9600 baud serial
console. Many other Arduino sketches default to 115200, so you may need to use
that speed if you want to see serial console output in the Arduino IDE. Any
Arduino board that is supported by IRRemote library will work with this.

#### TV Code
Your LG TV Service Menu password code might be different. I have read that 0000
is another common password, so try that if yours doesn't work. You can use any
normal LG remote to enter the code, you don't have to use this sketch for that
part - it's just a convenience.

## ASBL
Automatic Screen Brightness Leveling is a feature of LG OLED TVs that will
darken the entire screen after a few minutes of the TV being bright in only
part of the screen. In real usage, this can result in undesired darkening of
dark scenes that last for more than a few minutes in media, or in my case using
the TV as a computer monitor. If I didn't move my windows around much for a few
minutes, the screen was darkening more than I wanted, and I had to move a
brigher window around to make it "wake up" again. Please note that this feature
is enabled by default without easy access to turn it off because it is used to
extende the life of the OLED panel and reduce the risk of image burn-in. But, 
you gotta live, and I think this is a risk worth taking to enjoy my beautiful
OLED panel as I want to use. I would recommend using less than full brightness
and backlight when possible, and keep on the other OLED protection features like
pixel shifting and pixel refresher. And, if you're using it as a computer
monitor, your eyes will probably won't want full brightness at that closer
viewing range.

On the OLED48CXPUB, this setting is under menu item `12. OLED`, and it's the
first option, called `TPC Enable`. The default is `On` and I turned mine `Off`.
The settings takes effect immediately, after it is set you can use the Exit
button to go back to normal TV display mode.

## References
I used the `MKJ39170828` service remote to get the code for the `IN_START`
command. So, if you were thinking about buying an LG service remote just for the
`IN_START` command, you should be able to use this instead of buying the remote
(provided you have an Arduino and an IR LED. I scavenged my IR LED from a cheap
LED light strip remote control, basically any IR LED will work).

The raw code for opening the menu is `0x4FBFB04`, which is `0x4` for the address
byte and `0xFB` for the `IN_START` command. 

## Troubleshooting
If you have a built-in visible-light LED on your Arduino board (or if you add
one) then you can use it to see when the signal is being sent to the IR LED.
This is enabled in the line `IrSender.begin(3, true);`, where `3` is the IR LED
anode connection and `true` means to turn on that status indicator.

Another way you can troubleshoot the invisible IR LED is to use the camera app
on your phone - phone camera sensors will detect IR light and interpret it as
visible light, so you can watch the IR light blink and make sure it's
working/connected as intended. You don't even have to record it, just watch it
on the live preview.