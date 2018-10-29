/*
 * main.c
 *
 *  Created on: 2018 Oct 28 19:54:15
 *  Author: hdomingu
 */


#include "Drivers/MyoHand.h"
#include "Drivers/MyoDataCollector.h"

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

struct MyoHand handSignals;
struct FourTuple sensorReadings;

void InitializeLevels(struct MyoHand * myohandPtr);

//This samples the ADCs connected for the EMG sensors
void SampleEMGs(void)
{
	//Acknowledge interrupt and clear it
	TIMER_ClearEvent(&TIMER_0);
	DIGITAL_IO_SetOutputHigh(&OutputPin1);
	sensorReadings.thumb = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_thumbChannel);
	sensorReadings.index = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_indexChannel);
	sensorReadings.middle = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_middleChannel);
	sensorReadings.rp = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_rpChannel);
	MyoDataPush(&handSignals.sensorBuffer,&sensorReadings);
	DIGITAL_IO_SetOutputLow(&OutputPin1);
}

int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if(status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }


  /* 		INITIALIZATION OF VARIOUS COMPONENTS		*/
  MyoHandINIT(&handSignals);

  //enable sampling
  INTERRUPT_Enable(&samplingInterrupt);
  //Initialize Sensor Levels now that sampling is occurring at the set interrupt frequency
  //InitializeLevels(&handSignals);
  InitializeLevels(&handSignals);

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
	  //print Values
  }
}


//MUST BE CALLED --AFTER-- SAMPLING IS ALLOWED TO OCCUR VIA INTERRUPTS
//5 seconds resting to compute yR - resting level for each channel
//5 seconds contracted to compute yC - comfortable contraction level
void InitializeLevels(struct MyoHand * myohandPtr)
{

	DIGITAL_IO_SetOutputHigh(&LEDpin);
	//RELAX MUSCLES
    //wait 5 seconds
    //GetActivationLevels() from hand this is the yC set
	delayMils(5000);
	myohandPtr->yR = myohandPtr->sensorBuffer.averages;
    //CONTRACT MUSCLES TO A COMFORTABLE LEVEL
	//wait 5 seconds
    //GetActivationLevels() from hand this is the yR set
	delayMils(5000);
	myohandPtr->yC = myohandPtr->sensorBuffer.averages;
	DIGITAL_IO_SetOutputLow(&LEDpin);
}
