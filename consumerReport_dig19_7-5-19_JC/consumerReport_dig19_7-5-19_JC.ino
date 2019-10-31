/* Arduino USB Keyboard HID
   Digit Prototype Code
   Made by Shipmun

   With credit due to:
   Evan Kale https://github.com/evankale/ArduinoBTPS2
   Brian Lough https://www.youtube.com/channel/UCezJOfu7OtqGzd5xrP3q6WA
   Albert van der Meer https://www.instructables.com/id/Bluetooth-Bike-Audio-Remote/

*/

#include "LowPower.h"

// The (WIP) name of this device is Midgit (Media-Digit). It is a bluetooth media device controller, primarily for controlling music.

#define PoTPin 10    //4    pointer  top         Volume Up    
                     //     _        _           _16         
 
#define PoBPin A2    //8    pointer  bottom      Volume Down           
                     //     _        _           _32         

#define MTPin 9      //3    middle   top          Play-Pause          
                     //     _        _           _128            

#define MBPin 8      //10   middle   bottom      Mute           
                     //     _        _           _64        

#define RTPin A5     //12   ring     top         Next Track            
                     //     _        _           _256         

#define RBPin A4     //14   ring     bottom      Prev Track            
                     //     _        _           _512         

#define PiTPin 5     //16   pinkie   top         Activate device for a set time            
                     //     _        _           ____         

//#define PiBPin 2     //18   pinkie   bottom      Instantly re-enable sleep           
                     //     _        _           ____          
                     

#define LED_PIN1 A7

const int wakeUpPin = 2;

void wakeUp()
{
  // Just a handler for the pin interrupt.
}

int state = 1;
int mode = 1; //mode == 1 is typing default, mode == 2 is typing alternate, mode == 3 is typing numbers
bool shift = false;
unsigned long currentMillisSlp = 0;
unsigned long previousMillisSlp = 0;
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillisTwo = 0;
int ledState = LOW;             // ledState used to set the LED
int ledStateTwo = LOW;
const int ledPin =  2;// the number of the LED pin
const long oneInterval = 100;
const long twoInterval = 250;
const long threeInterval = 500;
const long slpInterval = 5000;

//delay removal for inputs
unsigned long prevMil1 = 0;//These are the actual unsigned longs
unsigned long prevMil2 = 0;
unsigned long prevMil3 = 0;
unsigned long prevMil4 = 0;
unsigned long prevMil5 = 0;
unsigned long prevMil6 = 0;
unsigned long prevMil7 = 0;
unsigned long prevMil8 = 0;


unsigned long *previousMillis1;//These are the pointers to the unsigned longs
unsigned long *previousMillis2;
unsigned long *previousMillis3;
unsigned long *previousMillis4;
unsigned long *previousMillis5;
unsigned long *previousMillis6;
unsigned long *previousMillis7;
unsigned long *previousMillis8;


bool hd1 = false;//These are the actual bools
bool hd2 = false;
bool hd3 = false;
bool hd4 = false;
bool hd5 = false;
bool hd6 = false;
bool hd7 = false;
bool hd8 = false;


bool *hold1;//These are the pointers to the bools
bool *hold2;
bool *hold3;
bool *hold4;
bool *hold5;
bool *hold6;
bool *hold7;
bool *hold8;



void setup()
{
  Serial.begin(115200);
  pinMode(MTPin, INPUT_PULLUP);
  pinMode(PoTPin, INPUT_PULLUP);
  pinMode(PoBPin, INPUT_PULLUP);
  pinMode(MBPin, INPUT_PULLUP);
  pinMode(RTPin, INPUT_PULLUP);
  pinMode(RBPin, INPUT_PULLUP);
  pinMode(PiTPin, INPUT_PULLUP);
  //pinMode(PiBPin, INPUT_PULLUP);
  pinMode(wakeUpPin, INPUT_PULLUP);   
  // enable internal pull-ups
  pinMode(LED_PIN1, OUTPUT); //enable LED indicator
  pinMode(LED_BUILTIN, OUTPUT); //enable LED indicator

  previousMillis1 = &prevMil1;//assigning pointers to the addresses of the unsigned longs
  previousMillis2 = &prevMil2;
  previousMillis3 = &prevMil3;
  previousMillis4 = &prevMil4;
  previousMillis5 = &prevMil5;
  previousMillis6 = &prevMil6;
  previousMillis7 = &prevMil7;
  previousMillis8 = &prevMil8;


  hold1 = &hd1;//assigning pointers to the addresses of the bools
  hold2 = &hd2;
  hold3 = &hd3;
  hold4 = &hd4;
  hold5 = &hd5;
  hold6 = &hd6;
  hold7 = &hd7;
  hold8 = &hd8;


  delay(200);
}

void loop()
{


  delay(1);        // delay in between reads for stability

  //check to see if it's been 5 seconds since waking up

  
  currentMillisSlp = millis();
  if (currentMillisSlp - previousMillisSlp >= slpInterval) {
    previousMillisSlp = currentMillisSlp;

    // Allow wake up pin to trigger interrupt on low.
    attachInterrupt(0, wakeUp, LOW);

    // Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                  SPI_OFF, USART0_OFF, TWI_OFF);

    // Disable external pin interrupt on wake up pin.
    detachInterrupt(0);
  }

  state = digitalRead(PoTPin);
  if (state != 1 && keypressCheck(previousMillis1, hold1)) {
    shift = false; Serial.write(253);   // 0xFD raw report key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0x10);    // volume up key
    Serial.write(0);
    Serial.write(253);   // release key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0);
    Serial.write(0);
  }


  state = digitalRead(PoBPin);
  if (state != 1 && keypressCheck(previousMillis2, hold2)) {
    shift = false; Serial.write(253);   // 0xFD raw report key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0x20);    // volume down key
    Serial.write(0);
    Serial.write(253);   // release key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0);
    Serial.write(0);
    previousMillisSlp = millis(); // reset timer to keep glove awake
  }

  state = digitalRead(MTPin);
  if (state != 1 && keypressCheck(previousMillis3, hold3)) {
    shift = false; Serial.write(253);   // 0xFD raw report key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0x80);    // play-pause key
    Serial.write(0);
    Serial.write(253);   // release key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0);
    Serial.write(0);
    previousMillisSlp = millis(); // reset timer to keep glove awake
  }

  state = digitalRead(MBPin);
  if (state != 1 && keypressCheck(previousMillis4, hold4)) {
    shift = false; Serial.write(253);   // 0xFD raw report key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0x40);    // mute key
    Serial.write(0);
    Serial.write(253);   // release key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0);
    Serial.write(0);
    previousMillisSlp = millis(); // reset timer to keep glove awake
  }

  state = digitalRead(RTPin);
  if (state != 1 && keypressCheck(previousMillis5, hold5)) {
    shift = false; Serial.write(253);   // 0xFD raw report key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0);    // next track key
    Serial.write(0x01);
    Serial.write(253);   // release key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0);
    Serial.write(0);
    previousMillisSlp = millis(); // reset timer to keep glove awake
  }

  state = digitalRead(RBPin);
  if (state != 1 && keypressCheck(previousMillis6, hold6)) {
    shift = false; Serial.write(253);   // 0xFD raw report key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0);    // prev track key
    Serial.write(0x02);
    Serial.write(253);   // release key
    Serial.write(3);
    Serial.write(3);
    Serial.write(0);
    Serial.write(0);
    previousMillisSlp = millis(); // reset timer to keep glove awake
  }
  
  state = digitalRead(PiTPin); // checking to see if glove should instantly go back to sleep
  if (state != 1 && keypressCheck(previousMillis1, hold1)) {
    if (previousMillisSlp > slpInterval) {
      previousMillisSlp -= slpInterval;
    }
    else {
      previousMillisSlp = 0;
    }
  }

}//End Loop_______________________________END LOOP________________________________




//BEGIN OTHER FUNCTIONS

//currently unused
void modeIndicator() {
  unsigned long currentMillis = millis();

  if (mode == 1) {
    if (currentMillis - previousMillis >= oneInterval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(LED_BUILTIN, ledState);
    }
  }
  else if (mode == 2) {
    if (currentMillis - previousMillis >= twoInterval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(LED_BUILTIN, ledState);
    }
  }
  else if (mode == 3) {
    if (currentMillis - previousMillis >= threeInterval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(LED_BUILTIN, ledState);
    }
  }

}

//currenty unused
void shiftIndicator() {
  unsigned long currentMillisTwo = millis();

  if (shift == true) {
    if (currentMillisTwo - previousMillisTwo >= oneInterval) {
      // save the last time you blinked the LED
      previousMillisTwo = currentMillisTwo;

      // if the LED is off turn it on and vice-versa:
      if (ledStateTwo == LOW) {
        ledStateTwo = HIGH;
      } else {
        ledStateTwo = LOW;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(LED_PIN1, ledStateTwo);
    }
  }
  else if (shift == false) {
    if (currentMillisTwo - previousMillisTwo >= threeInterval) {
      // save the last time you blinked the LED
      previousMillisTwo = currentMillisTwo;

      // if the LED is off turn it on and vice-versa:
      if (ledStateTwo == LOW) {
        ledStateTwo = HIGH;
      } else {
        ledStateTwo = LOW;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(LED_PIN1, ledStateTwo);
    }
  }

}


bool keypressCheck(unsigned long *prevTime, bool *curHold) {

  unsigned long currentMillisTwo = millis();

  unsigned long timeElapsed = currentMillisTwo - *prevTime;

  if (timeElapsed >= 100) {
    *curHold = false;
  }

  if (*curHold == true && timeElapsed > 75 && timeElapsed < 100) {//if THIS timer is between 75 and 100 ms AND THIS hold is true, send keypress and set THIS timer to 0
    *prevTime = currentMillisTwo;
    return true;
  }
  else if (timeElapsed >= 220 && timeElapsed < 225) {//else if THIS timer is between 220 and 225 ms, send keypress and set THIS hold to true and set THIS timer to 0
    *prevTime = currentMillisTwo;
    *curHold = true;
    return true;
  }
  else if (timeElapsed >= 225) {//else if THIS timer is > 225 ms, send keypress and set THIS hold to false and set THIS timer to 0
    *prevTime = currentMillisTwo;

    *curHold = false;
    return true;
  }
  else {

    return false;
  }
}
