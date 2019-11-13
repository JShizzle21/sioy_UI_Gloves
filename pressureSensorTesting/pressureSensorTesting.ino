#include <math.h>

int myPin = A0;  
int touching = false;
int touchingCount = 0;

void setup() {
  pinMode(A0, INPUT_PULLUP);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  int sensorValue = analogRead(myPin);
  Serial.println(sensorValue);
  delay(10);
}
