#include <Filters.h>

int val = 0;
int val2 = 0;
int filt_val = 0;
char topbyte = 0;
char bottombyte = 0;
float filterFrequency = 1.0;
 
// create a one pole (RC) lowpass filter
FilterOnePole lowpassFilter( LOWPASS, filterFrequency );


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A0);
  val2 = analogRead(A1);
  lowpassFilter.input(val);
  filt_val = lowpassFilter.output();
  Serial.println(filt_val);
  Serial.println(val2);
  if(filt_val > 200){
    digitalWrite(2,HIGH);
    }
  else{
    digitalWrite(2,LOW);
    }
  //topbyte = val/256;
  //bottombyte = val%256;
  //Serial.write(topbyte);
  //Serial.write(bottombyte);
}
