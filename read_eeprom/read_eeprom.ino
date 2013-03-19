#include <HAB.h>

#include <EEPROM.h>

int eepValue = 0;
int eepAddr = 0;
float voltage = 0;
float temperature = 0.0;

HAB hab;

void setup() {
  Serial.begin(115200);
  eepValue = EEPROM.read(eepAddr);
  Serial.print(int(hab.interval()), HEX); //first display time between readings in seconds
  //Only read portion of the memory that's been used
  while (eepAddr < 1023 && eepValue != 255) {
    Serial.print(eepValue, HEX);
    eepAddr++;
  }
}

void loop() {
  //no main loop necessary
}
