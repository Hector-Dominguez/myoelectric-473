#include <Filters.h>

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
#define INDEXIN A0
#define PINKYIN A1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(INDEXOUT,OUTPUT);
  pinMode(PINKYOUT,OUTPUT);
}

void loop() { //implements a task which will run at Fs > 2Fc
 //--------------------------------------Reading Interface Function-------------------------//
  //Reading of each myoelectric sensor
  indexRAW = analogRead(INDEXIN);
  pinkyRAW = analogRead(PINKYIN);
  

  //filtering of each sensor value  
  lowpassFilter1.input(indexRAW);
  indexFILTERED = lowpassFilter1.output();
  
  lowpassFilter2.input(pinkyRAW);
  pinkyFILTERED= lowpassFilter2.output();
 //--------------------------------------Reading Interface Function-------------------------//



  //prints to serial usb port to computer
  Serial.println(indexFILTERED);
  //Serial.println(pinkyFILTERED);

  //--------------------------------------Data Interpretation--------------------------------//
//  if(pinkyFILTERED > 200)
//  {
//    digitalWrite(PINKYOUT,HIGH);
//  }
//  else
//  {
//    digitalWrite(PINKYOUT,LOW);
//  }

  
  if(indexFILTERED > 200)
  {
    digitalWrite(INDEXOUT,HIGH);
  }
  else
  {
    digitalWrite(INDEXOUT,LOW);
  }

  
  //topbyte = val/256;
  //bottombyte = val%256;
  //Serial.write(topbyte);
  //Serial.write(bottombyte);
}
