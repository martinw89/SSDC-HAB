//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//NOTE: THIS ERASES ALL EEPROM MEMORY
//PROCEED WITH EXTREME CAUTION AND ONLY UPLOAD IF YOU KNOW WHY YOU'RE ERASING THE EEPROM!!!!
//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <EEPROM.h>

void setup() {
  //Erase all EEPROM memory. No turning back now.
  for (int eepByte = 0; eepByte < 1023; eepByte++) {
    EEPROM.write(eepByte, 255);
  }
}

void loop() {
  //main loop is unnecessary
}

