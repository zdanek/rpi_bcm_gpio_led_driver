#include <wiringPi.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

int const dataPin = 7;        //Define which pins will be used for the Shift Register control
int const latchPin = 9;
int const clockPin = 8;
int const clearPin = 0;

int const OUTPUT_BITS = 80;
int const FALSE_BIT = 0;
int const TRUE_BIT = 1;
int const RESOLUTION = 400;
typedef char byte;

//char const HIGH = 1;
//char const LOW = 0;


#define PRODUCTION

#ifndef PRODUCTION
#define DEBUG(MSG) printf(MSG)
#define DEBUGN(MSG) printf(MSG)
#define DEBUGHEX(LONG) printf("%#010x\n", LONG)
#define DEBUG_BYTES(BYTES, LENGTH) { for (dc = 0; dc < LENGTH; dc++) printf("%d", BYTES[dc]); printf("\n");}
//printf("%i", BYTES[dc]); }
#else
#define DEBUGHEX(LONG)
#define DEBUG(MSG)
#define DEBUGN(MSG)
#define DEBUG_BYTES(BYTES, LENGTH)
#endif

#define DELAY(ms) delay(ms);

void loop();
void setup();
void tickClock();
void tickLatch();
void dataClear();
void pushToRegister(byte data[]);

int main() {
    printf("WiringPi FTW!\n");

    setup();
    while(1) {
        loop();
    }
}

void setup() {
	wiringPiSetup();
    pinMode(dataPin, OUTPUT);       //Configure each IO Pin
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(clearPin, OUTPUT);

    digitalWrite(latchPin, LOW);
    digitalWrite(clockPin, LOW);
    digitalWrite(clearPin, HIGH);

    #ifndef PRODUCTION
  //  Serial.begin(9600);
    #endif

    DEBUG("Hello!");
}

void loop() {
    int i, j, dc;
    byte ledValues[OUTPUT_BITS];
   struct timespec tim, tim2;
   tim.tv_sec = 0;
   tim.tv_nsec = 10;

        ledValues[0] = (byte) RESOLUTION*100/100;
        ledValues[1] = (byte) RESOLUTION*20/100;
        ledValues[2] = (byte) RESOLUTION*20/100;
        ledValues[3] = (byte) RESOLUTION*30/100;
        ledValues[4] = (byte) RESOLUTION*40/100;
        ledValues[5] = (byte) RESOLUTION*60/100;
        ledValues[6] = (byte) RESOLUTION*80/100;
        ledValues[7] = (byte) RESOLUTION*100/100;

  DEBUG("VALUES");
  DEBUG_BYTES(ledValues, 8);  
      char outputWord[OUTPUT_BITS];

        while (1) {

            for (i = 0; i < RESOLUTION; i++) {
                for (j = 0; j < OUTPUT_BITS; j++) {
                    outputWord[j] = ledValues[j] > i; //? TRUE_BIT : FALSE_BIT;
                }

                pushToRegister(outputWord);
                nanosleep(&tim, &tim2);
            }
        }

}

void pushToRegister(byte data[]) {
    int i;
    int dc;
    DEBUG("Pushing to reg");
    DEBUG_BYTES(data, OUTPUT_BITS);
//    dataClear();

    for (i = 0; i < OUTPUT_BITS ; i++) {
        digitalWrite(dataPin, data[OUTPUT_BITS - i -1]);// == FALSE_BIT ? LOW : HIGH);
        tickClock();
    }

    tickLatch();

    #ifndef PRODUCTION
    DELAY(1000);
    #endif
   
}

void dataClear() {
    digitalWrite(clearPin, LOW);
//    DELAY(20);
    digitalWrite(clearPin, HIGH);
}

void tickClock() {
    digitalWrite(clockPin, HIGH);
//    DELAY(1);
    digitalWrite(clockPin, LOW);
}

void tickLatch() {
    digitalWrite(latchPin, HIGH);
//    DELAY(1);
    digitalWrite(latchPin, LOW);
}


//OE pulled high

//OE pulled low

//LOOP
//Data Clear
//DataIn clock - wsuwa dane
//DataStore - kopiuje
