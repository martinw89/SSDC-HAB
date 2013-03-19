#include <Hellschreiber.h>

Hellschreiber hell(13,8150); //initialize hellschreiber with pin and speed

void setup(){
  Serial.begin(9600);
}

void loop(){
  char message[] = ">>>mikeseese.com rocks >>> abcdefghijklmnopqrstuvwxyz0123456789|+ ";
  hell.sendMessage(message, sizeof(message));
}
