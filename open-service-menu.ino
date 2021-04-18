#include <Arduino.h>
#include <IRremote.h>

void setup() {
  // set the built-in output LED on a nano board to OUTPUT mode
  pinMode(LED_BUILTIN, OUTPUT);
  // start serial console at 9600 baud (for arduino nano clone)
  Serial.begin(9600);

  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Specify IR send pin 3 and enable feedback LED at default feedback LED pin (LED_BUILTIN)
  IrSender.begin(3, true);

  // IR send address bytes (LG code)
  uint16_t sAddress = 0x4;
  // IR send number of times to repeat signal. 
  // I guess you could increase this if your TV has trouble receiving the signal?
  uint8_t sRepeats = 0;
  // wait .5 second after boot to send the command
  delay(500);  
  Serial.println(F("Sending LG OLED IN_START command"));
  // send IN_START command to open the service menu password prompt
  IrSender.sendNEC(sAddress, 0xFB, sRepeats);
  // wait 2000ms for the password prompt to appear (though it appears to accept input before appearing on-screen)
  delay(2000);
  Serial.println(F("Sending LG OLED digits 0, 4, 1, 3 as passcode for IN_START command"));
  // send digit 0
  IrSender.sendNEC(sAddress, 0x10, sRepeats);
  // wait 500ms
  delay(500);
  // send digit 4
  IrSender.sendNEC(sAddress, 0x14, sRepeats);
  // wait 500ms
  delay(500);
  // send digit 1
  IrSender.sendNEC(sAddress, 0x11, sRepeats);
  // wait 500ms
  delay(500);
  // send digit 3
  IrSender.sendNEC(sAddress, 0x13, sRepeats);
}

/*
 * Set up the data to be sent.
 * For most protocols, the data is build up with a constant 8 (or 16 byte) address
 * and a variable 8 bit command.
 * There are exceptions like Sony and Denon, which have 5 bit address.
 */


void loop() {
  // don't send anything else
}
