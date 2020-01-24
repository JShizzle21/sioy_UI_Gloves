#include <math.h>

int myPin = A0;  
int touching = false;
int touchingCount = 0;
bool isOn = false;
int sensorValue = -1;
unsigned long prevMil = 0;
unsigned long curMil = 0;
unsigned long prevMil2 = 0; //used for serial monitor
unsigned long curMil2 = 0; //used for serial monitor
unsigned long prevMil3 = 0;
unsigned long curMil3 = 0;
int interval3 = 100; //minimum time between button presses <--bad, should fix
int interval = 20;
int interval2 = 5000; //used for serial monitor
int newRead = 0;
int tempArray[6] = {300,300,300,300,300,300};
int readArray[6] = {300,300,300,300,300,300};
int prevAvgRead = 300;
int newAvgRead = 300;
int threshold = 70;

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
  delay(1);
}

bool trigger() {
  curMil = millis();
  curMil3 = curMil;
  newRead = sensorValue;
  if (curMil - prevMil > interval) {//this if statement determines the new average reads
    for(int i = 0; i < 6; i++) {
      tempArray[i] = readArray[i];
    }
    for(int i = 0; i < 5; i++) {
      readArray[i] = tempArray[i+1];
    }
    readArray[5] = newRead;
    
    prevAvgRead = (readArray[0]+readArray[1]+readArray[2])/3;
    newAvgRead = (readArray[3]+readArray[4]+readArray[5])/3;
    
    if (prevAvgRead - newAvgRead > threshold && curMil3 - prevMil3 > interval3) {
      prevMil = millis();
      prevMil3 = curMil3;
      return true;
    }
    else return false;
  }
  else return false;
}
