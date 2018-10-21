#include <Filters.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <string.h>

int indexRAW = 0;
int pinkyRAW = 0;

int indexFILTERED = 0;
int pinkyFILTERED = 0;

char topbyte = 0;
char bottombyte = 0;
float filterFrequency = 1.0;
 
// create a one pole (RC) lowpass filter
FilterOnePole lowpassFilter1( LOWPASS, filterFrequency );
FilterOnePole lowpassFilter2( LOWPASS, filterFrequency );

//OUTPUTS of myo-processing
#define INDEXOUT 13
#define PINKYOUT 12

//Myoelectric Inputs
#define THUMBIN A0
#define INDEXIN A1
#define MIDDLEIN A2
#define RINGPINKYIN A3

#define INITBUTTON 2

/*
 * My propositon:
 * Make a task which samples the ADC value for the myos
 * Make another task which runs the filtering(averaging) and updating the output/motor positions/proportional control
 */
 
/* ------------------------------------------- Myoelectric Interface ------------------------------------------------------------------------------------*/

struct fourTuple
{
  int thumb;
  int index;
  int middle;
  int ringPinky;
};


/*----specific for our app-----*/
struct MyoDataBuffer
{
  fourTuple dataBuf[1024];
};

 struct MyoSensor
 {
   int channelNumber;
   int actuatorUpdateFrequency;
   int Yc; //comfortable contraction level parameter
   int Yr; //resting levels
   int YVALi;
   
 };
 
//this returns YVALi, the output of the filter;
int read(MyoSensor * thisSensor)
{
  return 0; 
}    
 //This function will run at aproximately 1kHz
void myoSampleTask(void * pvParameters)
{
  //sample INDEXIN,THUMBIN,MIDDLEIN,RINGPINKYIN : channel numbers
  //place each read value into the buffer of (thumb,idx,mid,rp) tuples
    (void) pvParameters;

  TickType_t xLastWakeTime;
  const TickType_t xPeriod = 1;
  xLastWakeTime = xTaskGetTickCount();

  volatile int i = 0;
  for (;;) // A Task shall never return or exit.
  {
    vTaskDelayUntil( &xLastWakeTime, xPeriod);
    //digitalWrite(taskOne, HIGH);
    
    //digitalWrite(taskOne, LOW);
  }
  return;
}

//this function is a task which will run at the actuatorUpdateFrequency
void processDataTask(void * pvParameters)
{
  //gather YVALi for each channel and update the var;
    (void) pvParameters;

  TickType_t xLastWakeTime;
  const TickType_t xPeriod = 30;
  xLastWakeTime = xTaskGetTickCount();

  volatile int i = 0;
  for (;;) // A Task shall never return or exit.
  {
    vTaskDelayUntil( &xLastWakeTime, xPeriod);
    //digitalWrite(taskOne, HIGH);
    
    //digitalWrite(taskOne, LOW);
  }

  return;
}

//this function will gather Yc and Yr, along with means and stdDevs for the estimation algo (Executes upon the press of an init Button)
void InitializeSensor(MyoSensor * thisSensor, int channelNumber)
{
  thisSensor->channelNumber = channelNumber;
  pinMode(channelNumber, INPUT);
  long yRest;
  long yComfortable;


  Serial.println("Calculating yRest:");
  //calculate yRest (5 seconds rest)
  long yAccumulation = 0;
  int count = 0;
  while(count < 5000)
  {
    yAccumulation = analogRead(channelNumber) + yAccumulation;
    delay(1);
    count++;
  }
  Serial.println(yAccumulation);
  yRest = yAccumulation / count;
//  toPrint = "yRest(" + channelNumber;
//  catString =") = " + yRest;
//  toPrint = toPrint + catString;
  Serial.println(yRest);

  Serial.println("Calculating yComfortable:");
  //calculate yComfortable (5 seconds comfortable contraction)
  yAccumulation = 0;
  count = 0;
  while(count < 5000)
  { 
    yAccumulation = analogRead(channelNumber) + yAccumulation;
    delay(1);
    count++;
  }
  Serial.println(yAccumulation);
  yComfortable = yAccumulation / count;
  Serial.println(yComfortable);

  thisSensor->Yc = yComfortable;
  thisSensor->Yr = yRest;
   return;
 
}

//--------------------------- WHOLE HAND--------------//
struct MyoHand
{
  MyoSensor thumb;
  MyoSensor index;
  MyoSensor middle;
  MyoSensor ringPinky;
};

MyoHand Hand;


void InitializeFingers(void)
{
//  Serial.println("-------------Thumb");
//  InitializeSensor(&Hand.thumb,THUMBIN);
  Serial.println("-------------Index");
  InitializeSensor(&Hand.index,INDEXIN);
//  Serial.println("-------------Middle");
//  InitializeSensor(&Hand.middle,MIDDLEIN);
//  Serial.println("-------------RingPinky");
//  InitializeSensor(&Hand.ringPinky,RINGPINKYIN);
}

/* ------------------------------------------- Myoelectric Interface ------------------------------------------------------------------------------------*/
void setup() {
  
  pinMode(INITBUTTON,INPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
  // put your setup code here, to run once:
  Serial.begin(9600);

      xTaskCreate(
    myoSampleTask
    ,  (const portCHAR *)"Task One"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

    xTaskCreate(
    processDataTask
    ,  (const portCHAR *)"Task Two"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

    while(1)
    {
      bool on = digitalRead(INITBUTTON);
      Serial.println(on);
      if(on)
      {
        break;
      }
    }
    InitializeFingers();

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

  


void loop() { //implements a task which will run at Fs > 2Fc

}
