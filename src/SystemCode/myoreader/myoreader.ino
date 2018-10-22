#include <Filters.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <string.h>
#include <cQueue.h>

char topbyte = 0;
char bottombyte = 0;
float filterFrequency = 1.0;
 
// create a one pole (RC) lowpass filter
FilterOnePole lowpassFilter1( LOWPASS, filterFrequency);
FilterOnePole lowpassFilter2( LOWPASS, filterFrequency);

//OUTPUTS of myo-processing
#define INDEXOUT 13
#define PINKYOUT 12

//Myoelectric Inputs
#define THUMBIN A0
#define INDEXIN A1
#define MIDDLEIN A2
#define RINGPINKYIN A3
#define INITBUTTON 2

#define DataWindowSize 750
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
Queue_t MyoDataBuf;// -------------------------------------------------------------------------------Data buff




 struct MyoSensor
 {
   int channelNumber;
   int actuatorUpdateFrequency;
   int Yc; //comfortable contraction level parameter
   int Yr; //resting levels
   int YVALi;
   
 };
 
//this function will gather Yc and Yr, along with means and stdDevs for the estimation algo (Executes upon the press of an init Button)
void InitializeSensor(MyoSensor * thisSensor, int channelNumber)
{
  thisSensor->channelNumber = channelNumber;
  pinMode(channelNumber, INPUT);
  long yRest;
  long yComfortable;


  Serial.println("Calculating yRest:");
  //----------------------------------------------calculate yRest (5 seconds rest)
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
  Serial.println(yRest);

  Serial.println("Calculating yComfortable:");
  //----------------------------------------------------calculate yComfortable (5 seconds comfortable contraction)
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

MyoHand Hand; //---------------------------------------------------- Hand with Sensors


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

//this returns YVALi, the output of the filter;
int read(MyoSensor * thisSensor)
{
  return 0; 
}    

  fourTuple Qentry;
 //This function will run at aproximately 1kHz
void myoSampleTask(void)
{
  //uses hand
  //sample the channels for each
  Qentry.thumb = analogRead(THUMBIN); 
  Qentry.index = analogRead(INDEXIN);
  Qentry.middle = analogRead(MIDDLEIN);
  Qentry.ringPinky = analogRead(RINGPINKYIN); 
  //update the fourTuple
  q_pop(&MyoDataBuf,&Qentry);
  q_push(&MyoDataBuf,&Qentry);
  
  return;
}

//this function is a task which will run at the actuatorUpdateFrequency
void processDataTask(void)
{
  //gather YVALi for each channel and update the var;
  //thumb
  //index
  //middle
  //ringpinky
  return;
}

/* ------------------------------------------- Myoelectric Interface ------------------------------------------------------------------------------------*/
void setup() {
  
  pinMode(INITBUTTON,INPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
  Serial.begin(9600);
  //setup dequeue for data
  //Initialize Hand Sensors
  //Initialize Data Queue with values for processing

}

  


void loop() { //implements a task which will run at Fs > 2Fc
  myoSampleTask();
  processDataTask();
  //read data
  //proportionalize it for a servo
  //output to servo
}
