#include "Arduino.h"
#include "Hellschreiber.h"

/*
character format (3x5):
        KFA
        LGB
        MHC
        NID
        OJE

variable format:
        2-byte, 16-bit int 0b0ABCDEFGHIJKLMNO
        (note that the most significant bit is not used)
*/

int _pin = 13;

volatile char width=1; // width of characters, widen to slow speed

int spd = 8150; // synchronization, incr to make it slant upward

void Hellschreiber::rest(char times){while (times){times--;delayMicroseconds(spd);}}

void Hellschreiber::on(char restfor){digitalWrite(_pin, HIGH);rest(restfor);}
void Hellschreiber::off(char restfor){digitalWrite(_pin, LOW);rest(restfor);}

// CUSTOMIZE THE MESSAGE, OR GENERATE IT DYNAMICALLY!
//int message[]={AR,AR,AR,S,W,H,A,R,D,E,N,PR,C,O,M,SP,R,O,C,K,S,SP,AR,AR,AR,SP,A,B,C,D,E,FF,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,BK,SP};

Hellschreiber::Hellschreiber(int pin, int speed){
  pinMode(pin, OUTPUT);
  _pin = pin;
  spd = speed;
}

void Hellschreiber::sendMessage(char message[], int length){
    //int _message[sizeof(message)];
    char i;
    Serial.print(sizeof(message));
    Serial.print(":");
    Serial.println(length);
    Serial.println(message);

    for(i=0;i<length;i++){
        switch(message[i]){
            case 'a':
                sendChar(A);
                break;
            case 'b':
                sendChar(B);
                break;
            case 'c':
                sendChar(C);
                break;
            case 'd':
                sendChar(D);
                break;
            case 'e':
                sendChar(E);
                break;
            case 'f':
                sendChar(FF);
                break;
            case 'g':
                sendChar(G);
                break;
            case 'h':
                sendChar(H);
                break;
            case 'i':
                sendChar(I);
                break;
            case 'j':
                sendChar(J);
                break;
            case 'k':
                sendChar(K);
                break;
            case 'l':
                sendChar(L);
                break;
            case 'm':
                sendChar(M);
                break;
            case 'n':
                sendChar(N);
                break;
            case 'o':
                sendChar(O);
                break;
            case 'p':
                sendChar(P);
                break;
            case 'q':
                sendChar(Q);
                break;
            case 'r':
                sendChar(R);
                break;
            case 's':
                sendChar(S);
                break;
            case 't':
                sendChar(T);
                break;
            case 'u':
                sendChar(U);
                break;
            case 'v':
                sendChar(V);
                break;
            case 'w':
                sendChar(W);
                break;
            case 'x':
                sendChar(X);
                break;
            case 'y':
                sendChar(Y);
                break;
            case 'z':
                sendChar(Z);
                break;
            case '.':
                sendChar(PR);
                break;
            case ' ':
                sendChar(SP);
                break;
            case '>':
                sendChar(AR);
                break;
            case '|':
                sendChar(PR);
                break;
            case '+':
                sendChar(SQ);
                break;
            case '0':
                sendChar(n0);
                break;
            case '1':
                sendChar(n1);
                break;
            case '2':
                sendChar(n2);
                break;
            case '3':
                sendChar(n3);
                break;
            case '4':
                sendChar(n4);
                break;
            case '5':
                sendChar(n5);
                break;
            case '6':
                sendChar(n6);
                break;
            case '7':
                sendChar(n7);
                break;
            case '8':
                sendChar(n8);
                break;
            case '9':
                sendChar(n9);
                break;
            default:
                break;
        }
    }

    /*for(i=0;i<sizeof(message)/2;i++){
            sendChar(message[i]);
    }*/
}

void Hellschreiber::setWidth(char _width){
    width = _width;
}

void Hellschreiber::setSPD(int _spd){
    spd = _spd;
}

void Hellschreiber::sendChar(int tosend){
    char w;
    char bit;
    for(w=0;w<width*2;w++){ // left column
            off(1);
            for (bit=0;bit<5;bit++){
                            if ((tosend>>bit)&1) {on(1);} 
                            else {off(1);}
                    }       
            off(1);
            }
    for(w=0;w<width*2;w++){ // middle column
            off(1);
            for (bit=5;bit<10;bit++){
                            if ((tosend>>bit)&1) {on(1);} 
                            else {off(1);}
                    }       
            off(1);
            }
    for(w=0;w<width*2;w++){ // right column
            off(1);
            for (bit=10;bit<15;bit++){
                            if ((tosend>>bit)&1) {on(1);} 
                            else {off(1);}
                    }       
            off(1);
            }
    off(14); // letter space (1 column)
}