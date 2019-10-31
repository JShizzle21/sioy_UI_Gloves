/* Arduino USB Keyboard HID 
 * Digit Prototype Code
 */

#include <SoftwareSerial.h>


uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */
                     //#    Finger   Position    defaultKey   SHIFT   Alt    SHIFT   Number  SHIFT
                     //                          _Usage ID (Dec)
                     
#define PoTCPin 22   //1    pointer  thumbClose  backspace    N/A     exit   N/A     N/A     N/A
                     //     _        _           _42          _       _      _       _       _
                            
#define PoTFPin 23   //2    pointer  thumbFar    shift        N/A     N/A    N/A     N/A     N/A
                     //     _        _           _leftShift         _       _      _       _       _
                            
#define PoLPin 24     //3    pointer  left        alt          N/A     N/A    N/A     N/A     N/A
                     //     _        _           _226         _       _      _       _       _
                            
#define PoTPin 25    //4    pointer  top         spacebar     tab     g      G       7       "
                     //     _        _           _44          _43     _10dn  _10up   _36dn   _52up
                            
#define PoRPin 26    //5    pointer  right       t            T       .      ?       2       :
                     //     _        _           _23dn        _23up   _55dn  _56up   _31dn   _51up
                            
#define PoBPin 27    //6    pointer  bottom      enter        !       m      M       -       ^
                     //     _        _           _40dn        _30up   _16dn  _16up   _45dn   _35up
                            
#define MLPin 28     //7    middle   left        e            E       u      U       1       ;
                     //     _        _           _8dn         _8up    _24dn  _24up   _30dn   _51dn
                            
#define MTPin 29     //8    middle   top         a            A       k      K       8       &
                     //     _        _           _4dn         _4up    _14dn  _14up   _37dn   _36up
                            
#define MRPin 30     //9    middle   right       s            S       v      V       4       (
                     //     _        _           _22dn        _22up   _25dn  _25up   _33dn   _38up
                            
#define MBPin 31     //10   middle   bottom      l            L       j      J       +       #
                     //     _        _           _15dn        _15up   _13dn  _13up   _46up   _32up
                            
#define RLPin 32     //11   ring     left        i            I       f      F       3       )
                     //     _        _           _12dn        _12up   _9dn   _9up    _32dn   _39up
                            
#define RTPin 33     //12   ring     top         h            H       x      X       9       %
                     //     _        _           _11dn        _11up   _27dn  _27up   _38dn   _34up
                            
#define RRPin 34     //13   ring     right       r            R       w      W       6       [
                     //     _        _           _21dn        _21up   _26dn  _26up   _35dn   _47dn
                            
#define RBPin 35     //14   ring     bottom      d            D       q      Q       =       _
                     //     _        _           _7dn         _7up    _20dn  _20up   _46dn   _45up
                            
#define PiLPin 36    //15   pinkie   left        n            N       p      P       5       ]
                     //     _        _           _17dn        _17up   _19dn  _19up   _34dn   _48dn
                            
#define PiTPin 37    //16   pinkie   top         o            O       y      Y       0       $
                     //     _        _           _18dn        _18up   _28dn  _28up   _39dn   _33up
                            
#define PiRPin 38    //17   pinkie   right       comma        '       z      Z       /       backslash
                     //     _        _           _54dn        _52dn   _29dn  _29up   _56dn   _49dn
                            
#define PiBPin 39    //18   pinkie   bottom      c            C       b      B       @       *
                     //     _        _           _6dn         _6up    _5dn   _5up    _31up   _37up
                            

#define LED_PIN 4

SoftwareSerial mySerial(2, 3); // RX, TX

int state = 1;
int mode = 1; //mode == 1 is typing default, mode == 2 is typing alternate, mode == 3 is typing numbers
bool shift = false;
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillisTwo = 0;
int ledState = LOW;             // ledState used to set the LED
int ledStateTwo = LOW;
const int ledPin =  2;// the number of the LED pin
const long oneInterval = 100; 
const long twoInterval = 250; 
const long threeInterval = 500; 
const int leftShift = 2;

//delay removal for inputs
unsigned long prevMil1 = 0;//These are the actual unsigned longs
unsigned long prevMil2 = 0;
unsigned long prevMil3 = 0;
unsigned long prevMil4 = 0;
unsigned long prevMil5 = 0;
unsigned long prevMil6 = 0;
unsigned long prevMil7 = 0;
unsigned long prevMil8 = 0;
unsigned long prevMil9 = 0;
unsigned long prevMil10 = 0;
unsigned long prevMil11 = 0;
unsigned long prevMil12 = 0;
unsigned long prevMil13 = 0;
unsigned long prevMil14 = 0;
unsigned long prevMil15 = 0;
unsigned long prevMil16 = 0;
unsigned long prevMil17 = 0;
unsigned long prevMil18 = 0;

unsigned long *previousMillis1;//These are the pointers to the unsigned longs
unsigned long *previousMillis2;
unsigned long *previousMillis3;
unsigned long *previousMillis4;
unsigned long *previousMillis5;
unsigned long *previousMillis6;
unsigned long *previousMillis7;
unsigned long *previousMillis8;
unsigned long *previousMillis9;
unsigned long *previousMillis10;
unsigned long *previousMillis11;
unsigned long *previousMillis12;
unsigned long *previousMillis13;
unsigned long *previousMillis14;
unsigned long *previousMillis15;
unsigned long *previousMillis16;
unsigned long *previousMillis17;
unsigned long *previousMillis18;



bool hd1 = false;//These are the actual bools
bool hd2 = false;
bool hd3 = false;
bool hd4 = false;
bool hd5 = false;
bool hd6 = false;
bool hd7 = false;
bool hd8 = false;
bool hd9 = false;
bool hd10 = false;
bool hd11 = false;
bool hd12 = false;
bool hd13 = false;
bool hd14 = false;
bool hd15 = false;
bool hd16 = false;
bool hd17 = false;
bool hd18 = false;

bool *hold1;//These are the pointers to the bools
bool *hold2;
bool *hold3;
bool *hold4;
bool *hold5;
bool *hold6;
bool *hold7;
bool *hold8;
bool *hold9;
bool *hold10;
bool *hold11;
bool *hold12;
bool *hold13;
bool *hold14;
bool *hold15;
bool *hold16;
bool *hold17;
bool *hold18; 




void setup() 
{
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(36, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  // enable internal pull-ups
  pinMode(LED_BUILTIN, OUTPUT); //enable LED indicator
  pinMode(LED_PIN, OUTPUT); //enable LED indicator

previousMillis1 = &prevMil1;//assigning pointers to the addresses of the unsigned longs
previousMillis2 = &prevMil2;
previousMillis3 = &prevMil3;
previousMillis4 = &prevMil4;
previousMillis5 = &prevMil5;
previousMillis6 = &prevMil6;
previousMillis7 = &prevMil7;
previousMillis8 = &prevMil8;
previousMillis9 = &prevMil9;
previousMillis10 = &prevMil10;
previousMillis11 = &prevMil11;
previousMillis12 = &prevMil12;
previousMillis13 = &prevMil13;
previousMillis14 = &prevMil14;
previousMillis15 = &prevMil15;
previousMillis16 = &prevMil16;
previousMillis17 = &prevMil17;
previousMillis18 = &prevMil18;

hold1 = &hd1;//assigning pointers to the addresses of the bools
hold2 = &hd2;
hold3 = &hd3;
hold4 = &hd4;
hold5 = &hd5;
hold6 = &hd6;
hold7 = &hd7;
hold8 = &hd8;
hold9 = &hd9;
hold10 = &hd10;
hold11 = &hd11;
hold12 = &hd12;
hold13 = &hd13;
hold14 = &hd14;
hold15 = &hd15;
hold16 = &hd16;
hold17 = &hd17;
hold18 = &hd18; 

  delay(200);
}

void loop() 
{
  

  delay(1);        // delay in between reads for stability
  modeIndicator();
  shiftIndicator();
  state = digitalRead(PoLPin);  //checking which mode to go to
  if (state != 1 && keypressCheck(previousMillis1, hold1) ) {
    //delay(200);
    if (mode == 1) {
      mode = 2;
      
    }
    else if (mode == 2) {
      mode = 3;
      
    }
    else {
      mode = 1;
      
    }
  } 
  
  
  state = digitalRead(PoTFPin);  //checking if shift was clicked
  if (state != 1 && keypressCheck(previousMillis2, hold2)) {
    shift = true;
  } 

  if (shift == false) {          //THIS SECTION IS NON-SHIFTED
      if (mode == 1) {   //BEGIN DEFAULT TYPING MODE___________________________________________
      state = digitalRead(PoTCPin);
      if (state != 1 && keypressCheck(previousMillis3, hold3)) {
        buf[2] = 42;   // backspace
        mySerial.write(buf, 8); Serial.write(buf, 8); // 
        releaseKey();
      } 
      state = digitalRead(PoTPin);
      if (state != 1 && keypressCheck(previousMillis4, hold4)) {
        buf[2] = 44;   // spacebar
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
    
      state = digitalRead(PoRPin);
      if (state != 1 && keypressCheck(previousMillis5, hold5)) {
        buf[2] = 23;   // t key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
    
      state = digitalRead(PoBPin);
      if (state != 1 && keypressCheck(previousMillis6, hold6)) {
        buf[2] = 40;   // enter key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MLPin);
      if (state != 1 && keypressCheck(previousMillis7, hold7)) {
        buf[2] = 8;   // e key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MTPin);
      if (state != 1 && keypressCheck(previousMillis8, hold8)) {

        buf[0]=(uint8_t)0xFE;
        buf[1]=(uint8_t)0x1;
        buf[2]=(uint8_t)0x0;
        buf[3]=(uint8_t)0x04;

        
        //buf[2] = 4;   // a key
        mySerial.write(buf, 4); Serial.write(buf, 4); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MRPin);
      if (state != 1 && keypressCheck(previousMillis9, hold9)) {
        buf[2] = 22;   // s key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MBPin);
      if (state != 1 && keypressCheck(previousMillis10, hold10)) {
        buf[2] = 15;   // l key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RLPin);
      if (state != 1 && keypressCheck(previousMillis11, hold11)) {
        buf[2] = 12;   // i key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RTPin);
      if (state != 1 && keypressCheck(previousMillis12, hold12)) {
        buf[2] = 11;   // h key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RRPin);
      if (state != 1 && keypressCheck(previousMillis13, hold13)) {
        buf[2] = 21;   // r key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RBPin);
      if (state != 1 && keypressCheck(previousMillis14, hold14)) {
        buf[2] = 7;   // d key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiLPin);
      if (state != 1 && keypressCheck(previousMillis15, hold15)) {
        buf[2] = 17;   // n key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiTPin);
      if (state != 1 && keypressCheck(previousMillis16, hold16)) {
        buf[2] = 18;   // o key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiRPin);
      if (state != 1 && keypressCheck(previousMillis17, hold17)) {
        buf[2] = 54;   // comma key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiBPin);
      if (state != 1 && keypressCheck(previousMillis18, hold18)) {
        buf[2] = 6;   // c key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 

    }//END DEFAULT TYPING MODE
    
      if (mode == 2) {   //BEGIN ALTERNATE TYPING MODE__________________________________________________
      state = digitalRead(PoTCPin);
      if (state != 1 && keypressCheck(previousMillis3, hold3)) {
        buf[2] = 42;   // still backspace for now, but eventually this would exit to macro mode
        mySerial.write(buf, 8); Serial.write(buf, 8); // 
        mode2ReleaseKey();
      } 
      state = digitalRead(PoTPin);
      if (state != 1 && keypressCheck(previousMillis4, hold4)) {
        buf[2] = 10;   // g key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
    
      state = digitalRead(PoRPin);
      if (state != 1 && keypressCheck(previousMillis5, hold5)) {
        buf[2] = 55;   // . key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
    
      state = digitalRead(PoBPin);
      if (state != 1 && keypressCheck(previousMillis6, hold6)) {
        buf[2] = 16;   // m key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(MLPin);
      if (state != 1 && keypressCheck(previousMillis7, hold7)) {
        buf[2] = 24;   // u key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(MTPin);
      if (state != 1 && keypressCheck(previousMillis8, hold8)) {
        buf[2] = 14;   // k key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(MRPin);
      if (state != 1 && keypressCheck(previousMillis9, hold9)) {
        buf[2] = 25;   // v key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(MBPin);
      if (state != 1 && keypressCheck(previousMillis10, hold10)) {
        buf[2] = 13;   // j key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(RLPin);
      if (state != 1 && keypressCheck(previousMillis11, hold11)) {
        buf[2] = 9;   // f key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(RTPin);
      if (state != 1 && keypressCheck(previousMillis12, hold12)) {
        buf[2] = 27;   // x key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(RRPin);
      if (state != 1 && keypressCheck(previousMillis13, hold13)) {
        buf[2] = 26;   // w key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(RBPin);
      if (state != 1 && keypressCheck(previousMillis14, hold14)) {
        buf[2] = 20;   // q key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(PiLPin);
      if (state != 1 && keypressCheck(previousMillis15, hold15)) {
        buf[2] = 19;   // p key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(PiTPin);
      if (state != 1 && keypressCheck(previousMillis16, hold16)) {
        buf[2] = 28;   // y key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(PiRPin);
      if (state != 1 && keypressCheck(previousMillis17, hold17)) {
        buf[2] = 29;   // z key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(PiBPin);
      if (state != 1 && keypressCheck(previousMillis18, hold18)) {
        buf[2] = 5;   // b key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
    }//END ALTERNATE TYPING MODE
    
      if (mode == 3) {   ///BEGIN NUMBERS TYPING MODE____________________________________________
      state = digitalRead(PoTCPin);
      if (state != 1 && keypressCheck(previousMillis3, hold3)) {
        buf[2] = 42;   // still backspace for now, but eventually this would exit to macro mode
        mySerial.write(buf, 8); Serial.write(buf, 8); // 
        releaseKey();
      } 
      state = digitalRead(PoTPin);
      if (state != 1 && keypressCheck(previousMillis4, hold4)) {
        buf[2] = 36;   // 7 key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
    
      state = digitalRead(PoRPin);
      if (state != 1 && keypressCheck(previousMillis5, hold5)) {
        buf[2] = 31;   // 2 key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
    
      state = digitalRead(PoBPin);
      if (state != 1 && keypressCheck(previousMillis6, hold6)) {
        buf[2] = 45;   // - key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MLPin);
      if (state != 1 && keypressCheck(previousMillis7, hold7)) {
        buf[2] = 30;   // 1 (one) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MTPin);
      if (state != 1 && keypressCheck(previousMillis8, hold8)) {
        buf[2] = 37;   // 8 key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MRPin);
      if (state != 1 && keypressCheck(previousMillis9, hold9)) {
        buf[2] = 33;   // 4 key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MBPin);
      if (state != 1 && keypressCheck(previousMillis10, hold10)) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 46;   // + key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RLPin);
      if (state != 1 && keypressCheck(previousMillis11, hold11)) {
        buf[2] = 32;   // 3 key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RTPin);
      if (state != 1 && keypressCheck(previousMillis12, hold12)) {
        buf[2] = 38;   // 9 key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RRPin);
      if (state != 1 && keypressCheck(previousMillis13, hold13)) {
        buf[2] = 35;   // 6 key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RBPin);
      if (state != 1 && keypressCheck(previousMillis14, hold14)) {
        buf[2] = 46;   // = key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiLPin);
      if (state != 1 && keypressCheck(previousMillis15, hold15)) {
        buf[2] = 34;   // 5 key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiTPin);
      if (state != 1 && keypressCheck(previousMillis16, hold16)) {
        buf[2] = 39;   // 0 key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiRPin);
      if (state != 1 && keypressCheck(previousMillis17, hold17)) {
        buf[2] = 56;   // / (forward slash) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiBPin);
      if (state != 1 && keypressCheck(previousMillis18, hold18)) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 31;   // @ key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
    }//END NUMBERS TYPING MODE
  }//End non-shifted section
  else {          //THIS SECTION IS SHIFTED_-_-_-_-_-_-_-_-_-_-_-_-_-_-BEGIN SHIFTED_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    if (mode == 1) {   //BEGIN DEFAULT TYPING MODE___________________________________________
      state = digitalRead(PoTCPin);
      if (state != 1) {
        buf[2] = 42;   // backspace
        mySerial.write(buf, 8); Serial.write(buf, 8); // 
        releaseKey();
      } 
      state = digitalRead(PoTPin);
      if (state != 1) {
        buf[2] = 43;   // tab
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
    
      state = digitalRead(PoRPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 23;   // T key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
    
      state = digitalRead(PoBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 30;   // ! key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MLPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 8;   // E key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 4;   // A key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MRPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 22;   // S key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 15;   // L key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RLPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 12;   // I key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 11;   // H key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RRPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 21;   // R key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 7;   // D key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiLPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 17;   // N key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 18;   // O key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiRPin);
      if (state != 1) {
        buf[2] = 52;   // ' (single quote apostraphe) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 6;   // C key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 

    }//END DEFAULT TYPING MODE
    
      if (mode == 2) {   //BEGIN ALTERNATE TYPING MODE__________________________________________________
      state = digitalRead(PoTCPin);
      if (state != 1) {
        buf[2] = 42;   // still backspace for now, but eventually this would exit to macro mode
        mySerial.write(buf, 8); Serial.write(buf, 8); // 
        mode2ReleaseKey();
      } 
      state = digitalRead(PoTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 10;   // G key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
    
      state = digitalRead(PoRPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 56;   // ? key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
    
      state = digitalRead(PoBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 16;   // M key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(MLPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 24;   // U key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(MTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 14;   // K key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(MRPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 25;   // V key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(MBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 13;   // J key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(RLPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 9;   // F key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(RTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 27;   // X key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(RRPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 26;   // W key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(RBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 20;   // Q key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(PiLPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 19;   // P key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(PiTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 28;   // Y key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(PiRPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 29;   // Z key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
      state = digitalRead(PiBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 5;   // B key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        mode2ReleaseKey();
      } 
      
    }//END ALTERNATE TYPING MODE
    
      if (mode == 3) {   ///BEGIN NUMBERS TYPING MODE____________________________________________
      state = digitalRead(PoTCPin);
      if (state != 1) {
        buf[2] = 42;   // still backspace for now, but eventually this would exit to macro mode
        mySerial.write(buf, 8); Serial.write(buf, 8); // 
        releaseKey();
      } 
      state = digitalRead(PoTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 52;   // " (double quotation marks) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
    
      state = digitalRead(PoRPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 51;   // : (colon) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
    
      state = digitalRead(PoBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 35;   // ^ (carat) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MLPin);
      if (state != 1) {
        buf[2] = 51;   // ; (semicolon) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 36;   // & (and symbol) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MRPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 38;   // ( (open parenthesis) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(MBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 32;   // # (number sign) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RLPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 39;   // ) (close parenthesis) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 34;   // % (percent symbol) key
        releaseKey();
      } 
      
      state = digitalRead(RRPin);
      if (state != 1) {
        buf[2] = 47;   // [ (open bracket) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(RBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 45;   // _ (underscore) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiLPin);
      if (state != 1) {
        buf[2] = 48;   // ] (close bracket) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiTPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 33;   // $ (dollar sign) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiRPin);
      if (state != 1) {
        buf[2] = 49;   // \ (back slash) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
      
      state = digitalRead(PiBPin);
      if (state != 1) {
        buf[0] = leftShift;  // left shift key modifier
        buf[2] = 37;   // * (asterisk) key
        mySerial.write(buf, 8); Serial.write(buf, 8); // Send keypress
        releaseKey();
      } 
    }//END NUMBERS TYPING MODE
  }//End shifted section
}//End Loop_______________________________END LOOP________________________________

//BEGIN OTHER FUNCTIONS

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  mySerial.write(buf, 8); Serial.write(buf, 8); // Release key
  shift = false;  //reset shift
  //delay(100);
}

void mode2ReleaseKey() {
  buf[0] = 0;
  buf[2] = 0;
  mySerial.write(buf, 8); Serial.write(buf, 8); // Release key  
  shift = false; //reset shift
  mode = 1; //mode 2 automatically switches back to mode 1 after any keypress
  //delay(100);
}

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
      digitalWrite(LED_PIN, ledStateTwo);
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
      digitalWrite(LED_PIN, ledStateTwo);
    }
  }
  
}

bool keypressCheck(unsigned long *prevTime, bool *curHold) {
  
  unsigned long currentMillisTwo = millis();
  
  unsigned long timeElapsed = currentMillisTwo - *prevTime;
  //Serial.println("timeElapsed:");
  //Serial.println(timeElapsed);

  if (timeElapsed >= 100) {
    *curHold = false;
  }
  //Serial.println("curHold");
  //Serial.println(*curHold);
  
   if (*curHold == true && timeElapsed > 75 && timeElapsed < 100) {//if THIS timer is between 50 and 60 ms AND THIS hold is true, send keypress and set THIS timer to 0
    *prevTime = currentMillisTwo;
    return true;
  }
  else if (timeElapsed >= 220 && timeElapsed < 225) {//else if THIS timer is between 200 and 300 ms, send keypress and set THIS hold to true and set THIS timer to 0
    *prevTime = currentMillisTwo;
    *curHold = true;
    return true;
  }
  else if (timeElapsed >= 225) {//else if THIS timer is > 300 ms, send keypress and set THIS hold to false and set THIS timer to 0
    *prevTime = currentMillisTwo;
    
    *curHold = false;
    return true;
  }
  else {
    
    return false;
  }
}
