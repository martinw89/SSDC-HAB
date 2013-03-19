#ifndef Hellschreiber_h
#define Hellschreiber_h

#include "Arduino.h"

#define A       0b0111111010011111
#define B       0b0010101010111111
#define C       0b0100011000101110
#define D       0b0011101000111111
#define E       0b0100011010111111
#define FF      0b0100001010011111
#define G       0b0100111000101110
#define H       0b0111110010011111
#define I       0b0100011111110001
#define J       0b0111110000100011
#define K       0b0110110010011111
#define L       0b0000010000111111
#define M       0b0111110110011111
#define N       0b0011111000001111
#define O       0b0011101000101110
#define P       0b0010001010011111
#define Q       0b0111011001011110
#define R       0b0010111010011111
#define S       0b0100101010101001
#define T       0b0100001111110000
#define U       0b0111110000111111
#define V       0b0111100000111110
#define W       0b0111110001111111
#define X       0b0110110010011011
#define Y       0b0110000011111000
#define Z       0b0110011010110011
#define n0      0b0111111000111111
#define n1      0b0000011111101001
#define n2      0b0111011010110111
#define n3      0b0111111010110001
#define n4      0b0111110010011100
#define n5      0b0101111010111101
#define n6      0b0101111010111111
#define n7      0b0110001011110000
#define n8      0b0111111010111111
#define n9      0b0111111010111101
#define SP      0b0000000000000000
#define BK      0b0111111111111111
#define SQ      0b0001000111000100
#define PR      0b0000110001100011
#define AR      0b0001000111011111

class Hellschreiber
{
  public:
    Hellschreiber(int pin, int speed);
    void sendMessage(char message[], int length);
    void setWidth(char _width);
    void setSPD(int _spd);
  private:
  	void sendChar(int toSend);
  	void rest(char times);
  	void on(char restfor);
  	void off(char restfor);
    int _pin;
};

#endif