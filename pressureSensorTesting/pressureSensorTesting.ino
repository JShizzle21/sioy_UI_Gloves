#include <math.h>

int myPin = A0;  
int touching = false;
int touchingCount = 0;
bool isOn = false;
int sensorValue = -1;
unsigned long prevMil = 0;
unsigned long curMil = 0;
unsigned long prevMil2 = 0;
unsigned long curMil2 = 0;
unsigned long prevMil3 = 0;
unsigned long curMil3 = 0;
int interval3 = 500; //minimum time between button presses <--bad, should fix
int interval = 20;
int interval2 = 5000;
int prevRead = 0;
int newRead = 0;
int read1 = 300;
int read2 = 300;
int read3 = 300;
int read4 = 300;
int read5 = 300;
int read6 = 300;
int prevAvgRead = 300;
int newAvgRead = 300;
int timeline = 1; //values of 1,2,3,4,5,6


void setup() {
  pinMode(A0, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);
  
}

// the loop function runs over and over again forever
void loop() {
  sensorValue = analogRead(myPin);

  //float voltage = sensorValue / 1023.0 * 5;
  if (trigger()) {
    if (isOn) {
      digitalWrite(LED_BUILTIN, LOW);
      isOn = false;
    }
    else {
      digitalWrite(LED_BUILTIN, HIGH);
      isOn = true;
    }
  }
  Serial.println(prevAvgRead-newAvgRead);
  curMil2 = millis();
  if (curMil2 - prevMil2 > interval2) {
    prevMil2=curMil2;
    Serial.println(300);
    Serial.println(-300);
  }

  //Serial.println(prevAvgRead);
  //Serial.println(newAvgRead);
  //Serial.println("hi");
  delay(10);
}

bool trigger() {
  curMil = millis();
  curMil3 = curMil;
  newRead = sensorValue;
  if (curMil - prevMil > interval) {

    
    timeline++;
    if (timeline > 6) timeline = 1;
    if (timeline == 1) {
      read1 = sensorValue;
      prevAvgRead = read1+read2+read3/3;
      newAvgRead = read4+read5+read6/3;
    }
    if (timeline == 2) {
      read2 = sensorValue;
      prevAvgRead = read1+read2+read3/3;
      newAvgRead = read4+read5+read6/3;
    }
    if (timeline == 3) {
      read3 = sensorValue;
      prevAvgRead = read1+read2+read3/3;
      newAvgRead = read4+read5+read6/3;
    }
    if (timeline == 4) {
      read4 = sensorValue;
      prevAvgRead = read1+read2+read3/3;
      newAvgRead = read4+read5+read6/3;
    }
    if (timeline == 5) {
      read5 = sensorValue;
      prevAvgRead = read1+read2+read3/3;
      newAvgRead = read4+read5+read6/3;
    }
    if (timeline == 6) {
      read6 = sensorValue;
      prevAvgRead = read1+read2+read3/3;
      newAvgRead = read4+read5+read6/3;
    }

    
    if (prevAvgRead - newAvgRead > 90 && curMil3 - prevMil3 > interval3) {
      prevMil = millis();
      prevRead = sensorValue;
      prevMil3 = curMil3;
      return 1;
    }
    else {
      prevRead = sensorValue;
      return 0;
    }
  }
  else {
    prevRead = sensorValue;
    return 0;
  }
}
