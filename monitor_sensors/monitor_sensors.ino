/* This Arduino code will monitor HAB sensors and write readings to a MicroSD card */

#include <HAB.h>
#include <SD.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Hellschreiber.h>

Hellschreiber hell(4,8150);

//GPS communicates by serial
SoftwareSerial mySerial(3, 2);

HAB hab;

Adafruit_GPS GPS(&mySerial);
int tempPin = A0; //Analog input connected to temperature sensor
float temperature = 0.0; //in kelvin
uint32_t timer = millis(); //Loop timing
uint32_t radioTimer = millis();
File telemFile;
char tempChar[10];
String radioString;
char radioMessage[40];

boolean usingInterrupt = false;
void useInterrupt(boolean);

void setup() {
// Serial debugging - uncomment to see temp values in the serial window
  Serial.begin(9600);
  
  Serial.println("Init GPS...");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  useInterrupt(true);
  delay(1000);
  
  Serial.println("Init SD...");
  //Set pin 10 to output for SD
  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("SD initialization failed!");
    return;
  }
  Serial.println("SD initialization done.");
  delay(5000);
  telemFile = SD.open("TELEM.csv", FILE_WRITE);
  Serial.println("Successfully opened file.");
  telemFile.println("Time (sec),Temperature (K),Latitude (deg),N/S,Longitude (deg),E/W,Altitude (m)");
  telemFile.close();
  
  timer = millis();
}

//For GPS
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
}

//For GPS
void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

float getTemperature(int pin) {
  int digitalTemp; //Stores the raw 0-1023 value of the temperature
  float tempVoltage;
  float returnTemp; //in kelvin
  
  digitalTemp = analogRead(pin);
  tempVoltage = digitalTemp * (hab.vref() / 1023.0);
  //Gives the reading in degrees celsius. This math is done because the temperature sensor employs a 500mV offset and maps 10mV per degree. See temperature turorial in HAB dropbox for more details.
  returnTemp = (tempVoltage - 0.5)*100;
  returnTemp = returnTemp + 273.15; //Convert to Kelvin
  return(returnTemp);
}

void writeTelem(File telem, int time, float temp, float lat, char latns, float lon, char lonew, float alt) {
  telem.print(time);
  telem.print(",");
  telem.print(temp, 3);
  telem.print(",");
  telem.print(lat, 5);
  telem.print(",");
  telem.print(latns);
  telem.print(",");
  telem.print(lon, 5);
  telem.print(",");
  telem.print(lonew);
  telem.print(",");
  telem.print(alt,3);
  telem.print(",");
  telem.print("\n");
  
  return;
}

void loop() { 
  char latitude[8];
  char longitude[8];
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
  
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
  
  if(millis()-timer > 2000) {
    Serial.println("logging...");
    timer = millis();
    temperature = getTemperature(tempPin);
  
    //TODO: Pressure
    telemFile = SD.open("TELEM.csv", FILE_WRITE);
    telemFile.print(timer/1000.0);
     telemFile.print(",");
    telemFile.print(temperature, 3);
    telemFile.print(",");
    telemFile.print(GPS.latitude/100.0, 5);
    telemFile.print(",");
    telemFile.print(GPS.lat);
    telemFile.print(",");
    telemFile.print(GPS.longitude/100.0, 5);
    telemFile.print(",");
    telemFile.print(GPS.lon);
    telemFile.print(",");
    telemFile.print(GPS.altitude/100.0,3);
    telemFile.print(",");
    telemFile.print((int)GPS.fixquality);
    telemFile.print(",");
    telemFile.print((int)GPS.satellites);
    telemFile.print("\n");
    telemFile.close();
    
    if(millis() - radioTimer > 60000) {
      radioTimer = millis();
      radioString = "W4MIQ | ";
      dtostrf(GPS.latitude/100.0, 7, 4, latitude);
      radioString += latitude;
      radioString += " | ";
      dtostrf(GPS.longitude/100.0, 7, 4, longitude);
      radioString += longitude;
      radioString += " | ";
      dtostrf(temperature, 6, 2, tempChar);
      radioString += tempChar;
      radioString += "\0";
      radioString.toCharArray(radioMessage, 40);
      hell.sendMessage(radioMessage, sizeof(radioMessage));
    }
  }
}
