#include <Arduino_FreeRTOS.h>
#include <string.h>
#include <CircularBuffer.h>

char topbyte = 0;
char bottombyte = 0;

 
// create a one pole (RC) lowpass filter


//OUTPUTS of myo-processing
#define INDEXOUT 13
#define PINKYOUT 12

//Myoelectric Inputs
#define THUMBIN A0
#define INDEXIN A1
#define MIDDLEIN A2
#define RINGPINKYIN A3
#define INITBUTTON 2

#define DataWindowSize 500
/*
 * My propositon:
 * Make a task which samples the ADC value for the myos
 * Make another task which runs the filtering(averaging) and updating the output/motor positions/proportional control
 */
 
/* ------------------------------------------- Myoelectric Interface ------------------------------------------------------------------------------------*/

struct FourTuple
{
  int thumb;
  int index;
  int middle;
  int ringPinky;
};

 class MyoSensor
 {
   public:
     int Yc; //comfortable contraction level parameter
     int Yr; //resting levels
     int yFilt;
     int YVALi;
     long prevAvgNumerator;
     //this returns YVALi, the output of the filter;
     int read(void)
     {
       return this->YVALi; 
     }    
  
     //this function will gather Yc and Yr, along with means and stdDevs for the estimation algo (Executes upon the press of an init Button)
    void InitializeSensor(int channelNumber)
    {
      pinMode(channelNumber, INPUT);
      long yRest;
      long yComfortable;

       //fill up
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
    
      this->Yc = yComfortable;
      this->Yr = yRest;
      return;
    }
 };
 


//--------------------------- WHOLE HAND--------------//
class MyoHand
{
  public: 
  MyoSensor thumb;
  MyoSensor index;
  MyoSensor middle;
  MyoSensor ringPinky;
    void InitializeFingers(void)
  {
    //fill up dataQueue with values
  }
};

MyoHand Hand; //---------------------------------------------------- Hand with Sensors

//This function will run at aproximately 1kHz (assumes the buffer is filled already)
void myoSampleFilterTask(void)
{
  static CircularBuffer<FourTuple, DataWindowSize> dataBuffer;// -------------------------------------------------------------------------------Data buff
  //Initialize Data Queue with values for processing
  //Initialize averageValues in myos
  FourTuple Qentry;
  //sample the channels for each
  Qentry.thumb = analogRead(THUMBIN); 
  Qentry.index = analogRead(INDEXIN);
  Qentry.middle = analogRead(MIDDLEIN);
  Qentry.ringPinky = analogRead(RINGPINKYIN);
  //-------------------------compute sliding average for each channel
  FourTuple oldestQentry = dataBuffer.pop();
  Hand.thumb.yFilt = (Qentry.thumb + Hand.thumb.prevAvgNumerator - oldestQentry.thumb) / DataWindowSize;
  Hand.index.yFilt = (Qentry.index + Hand.index.prevAvgNumerator - oldestQentry.index) / DataWindowSize;
  Hand.middle.yFilt = (Qentry.middle + Hand.middle.prevAvgNumerator - oldestQentry.middle) / DataWindowSize;
  Hand.ringPinky.yFilt = (Qentry.ringPinky + Hand.ringPinky.prevAvgNumerator - oldestQentry.ringPinky) / DataWindowSize;
  //update the buffer
  dataBuffer.push(Qentry);
  return;
}

//this function is a task which will run at the actuatorUpdateFrequency (assumes an average has been calculated beforehand)
void processDataTask()
{
  //gather YVALi for each channel and update the var;
  //1) Grab filtered yVal and compute the normalized muscle activation value, YVALi
  Hand.thumb.YVALi = (Hand.thumb.yFilt - Hand.thumb.Yr)/(Hand.thumb.Yc-Hand.thumb.Yr);
  Hand.index.YVALi = (Hand.index.yFilt - Hand.index.Yr)/(Hand.index.Yc-Hand.index.Yr);
  Hand.middle.YVALi = (Hand.middle.yFilt - Hand.middle.Yr)/(Hand.middle.Yc-Hand.middle.Yr);
  Hand.ringPinky.YVALi = (Hand.ringPinky.yFilt - Hand.ringPinky.Yr)/(Hand.ringPinky.Yc-Hand.ringPinky.Yr);
  return;
}

/* ------------------------------------------- Myoelectric Interface ------------------------------------------------------------------------------------*/
void setup() {
  
  pinMode(INITBUTTON,INPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
  Serial.begin(9600);
  //Initialize Hand Sensors
}

  


void loop() { //implements a task which will run at Fs > 2Fc
  /*----specific for our app-----*/
  myoSampleFilterTask();
  processDataTask();
  //read data
  //proportionalize it for a servo
  //output to servo
}

// 10/21/18 -> Need to implement an efficient signal processing algo!
// average once for each signal and then implement a (subtract oldest add newest and then divide algorithm)
