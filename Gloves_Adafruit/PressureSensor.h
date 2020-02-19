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

int sensorValue[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long prevMil[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long curMil[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long prevMil2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long curMil2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int newRead[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int differenceArray[8][15] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //[number of buttons][number of differences stored]
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
}; 
int tempDifferenceArray[8][15] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //[number of buttons][number of differences stored]
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
}; 
int maxDiff[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int prevAvgRead[8] = {300, 300, 300, 300, 300, 300, 300, 300};
int newAvgRead[8] = {300, 300, 300, 300, 300, 300, 300, 300};
int tempArray[8][6] = {{300, 300, 300, 300, 300, 300}, //[number of buttons][number of reads used to determine averages]
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300}
};
int readArray[8][6] = {{300, 300, 300, 300, 300, 300}, //[number of buttons][number of reads used to determine averages]
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300},
  {300, 300, 300, 300, 300, 300}
};

int buttons[8] = {0, 1, 2, 3, 4, 5, 6, 7};

const int interval = 20; //minimum time between new average reads
const int interval2 = 3000;//101; //minimum time between button presses
const int threshold = 100;

bool triggers[8] = {0,0,0,0,0,0,0,0};

#define NUM_OF_PINS 8
