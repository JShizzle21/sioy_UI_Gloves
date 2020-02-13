#include <math.h>

int myPin0 = A0;
int myPin1 = A1;
int myPin2 = A2;
int myPin3 = A3;
int myPin4 = A4;
int myPin5 = A5;
int myPin6 = A6;
int myPin7 = A7;

int touching = false;
int touchingCount = 0;
bool isOn = false;
unsigned long prevMil4 = 0; //used for serial monitor
unsigned long curMil4 = 0; //used for serial monitor
int interval4 = 5000; //used for serial monitor

unsigned long curMilMinTime = 0;
unsigned long prevMilMinTime = 0;
const int intervalMinTime = 61;

int sensorValue[8] = {0,0,0,0,0,0,0,0};
unsigned long prevMil[8] = {0,0,0,0,0,0,0,0};
unsigned long curMil[8] = {0,0,0,0,0,0,0,0};
unsigned long prevMil2[8] = {0,0,0,0,0,0,0,0};
unsigned long curMil2[8] = {0,0,0,0,0,0,0,0};
int newRead[8] = {0,0,0,0,0,0,0,0};
int prevPrevPREVDifference[8] = {0,0,0,0,0,0,0,0};
int prevPrevDifference[8] = {0,0,0,0,0,0,0,0};
int prevDifference[8] = {0,0,0,0,0,0,0,0};
int prevAvgRead[8] = {300,300,300,300,300,300,300,300};
int newAvgRead[8] = {300,300,300,300,300,300,300,300};
int tempArray[8][6] = {{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300}};
int readArray[8][6] = {{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300},
{300,300,300,300,300,300}};

int buttons[8] = {0,1,2,3,4,5,6,7};

const int interval = 20; //minimum time between new average reads
const int interval2 = 100; //minimum time between button presses
const int threshold = 200;

void setup() {
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);
  
}

// the loop function runs over and over again forever
void loop() {
  sensorValue[0] = analogRead(myPin0);
  sensorValue[1] = analogRead(myPin1);
  sensorValue[2] = analogRead(myPin2);
  sensorValue[3] = analogRead(myPin3);
  sensorValue[4] = analogRead(myPin4);
  sensorValue[5] = analogRead(myPin5);
  sensorValue[6] = analogRead(myPin6);
  sensorValue[7] = analogRead(myPin7);

  //float voltage = sensorValue / 1023.0 * 5;
  if (trigger(0) && minTime()) {//button 1
  //  Serial.println("button1");
    if (isOn) {
      digitalWrite(LED_BUILTIN, LOW);
      isOn = false;
    }
    else {
      digitalWrite(LED_BUILTIN, HIGH);
      isOn = true;
    }
  }
  if (trigger(1) && minTime()) {//button 2
   // Serial.println("button2");
    if (isOn) {
      digitalWrite(LED_BUILTIN, LOW);
      isOn = false;
    }
    else {
      digitalWrite(LED_BUILTIN, HIGH);
      isOn = true;
    }
  }
  if (trigger(2) && minTime()) {//button 3
  //  Serial.println("button3");
    if (isOn) {
      digitalWrite(LED_BUILTIN, LOW);
      isOn = false;
    }
    else {
      digitalWrite(LED_BUILTIN, HIGH);
      isOn = true;
    }
  }
  if (trigger(3) && minTime()) {//button 4
  //  Serial.println("button4");
    if (isOn) {
      digitalWrite(LED_BUILTIN, LOW);
      isOn = false;
    }
    else {
      digitalWrite(LED_BUILTIN, HIGH);
      isOn = true;
    }
  }
  if (trigger(4) && minTime()) {//button 5
   // Serial.println("button5");
    if (isOn) {
      digitalWrite(LED_BUILTIN, LOW);
      isOn = false;
    }
    else {
      digitalWrite(LED_BUILTIN, HIGH);
      isOn = true;
    }
  }
  if (trigger(5) && minTime()) {//button 6
   // Serial.println("button6");
    if (isOn) {
      digitalWrite(LED_BUILTIN, LOW);
      isOn = false;
    }
    else {
      digitalWrite(LED_BUILTIN, HIGH);
      isOn = true;
    }
  }
/*  if (trigger(6) && minTime()) {//button 7
    Serial.println("button7");
    if (isOn) {
      digitalWrite(LED_BUILTIN, LOW);
      isOn = false;
    }
    else {
      digitalWrite(LED_BUILTIN, HIGH);
      isOn = true;
    }
  }
  if (trigger(7) && minTime()) {//button 8
    Serial.println("button8");
    if (isOn) {
      digitalWrite(LED_BUILTIN, LOW);
      isOn = false;
    }
    else {
      digitalWrite(LED_BUILTIN, HIGH);
      isOn = true;
    }
  }*/
  

  
  Serial.println(prevAvgRead[0]-newAvgRead[0]);
  curMil4 = millis();
  if (curMil4 - prevMil4 > interval4) {
    prevMil4=curMil4;
    Serial.println(600);
    Serial.println(-600);
  }

  //Serial.println(prevAvgRead);
  //Serial.println(newAvgRead);
  //Serial.println("hi");
  delay(10);
}

//TRIGGER FUNCTION:
bool trigger(int curButton) {
  curMil[curButton] = millis();
  curMil2[curButton] = curMil[curButton];
  newRead[curButton] = sensorValue[curButton];
  if (curMil[curButton] - prevMil[curButton] > interval) {//this if statement determines the new average reads
    prevPrevPREVDifference[curButton] = prevPrevDifference[curButton];
    prevPrevDifference[curButton] = prevDifference[curButton];
    prevDifference[curButton] = prevAvgRead[curButton] - newAvgRead[curButton];
  if (prevDifference[curButton] < 0) prevDifference[curButton] = 0;//attempt to reduce noise from finger bending
    
    for(int i = 0; i < 6; i++) {
      tempArray[curButton][i] = readArray[curButton][i];
    }
    for(int i = 0; i < 5; i++) {
      readArray[curButton][i] = tempArray[curButton][i+1];
    }
    readArray[curButton][5] = newRead[curButton];
    
    prevAvgRead[curButton] = (readArray[curButton][0]+readArray[curButton][1]+readArray[curButton][2])/3;
    newAvgRead[curButton] = (readArray[curButton][3]+readArray[curButton][4]+readArray[curButton][5])/3;

    if (((prevAvgRead[curButton] - newAvgRead[curButton]) - prevDifference[curButton] > threshold)                 //here is the threshold/change if statement
    || (((prevAvgRead[curButton] - newAvgRead[curButton]) - prevPrevDifference[curButton]) > threshold)
    || (((prevAvgRead[curButton] - newAvgRead[curButton]) - prevPrevPREVDifference[curButton]) > threshold)
    && curMil2[curButton] - prevMil2[curButton] > interval2) {
      prevMil[curButton] = millis();
      prevMil2[curButton] = curMil2[curButton];
      return true;
    }
    else return false;
  }
  else return false;
}

bool minTime() {
  curMilMinTime = millis();
  if (curMilMinTime - prevMilMinTime > intervalMinTime) {
    prevMilMinTime = curMilMinTime;
    return true;
  }
  return false;
}
