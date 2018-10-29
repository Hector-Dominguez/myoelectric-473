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

//This samples the ADCs connected for the EMG sensors
void SampleEMGs(void)
{
	//Acknowledge interrupt and clear it
	TIMER_ClearEvent(&TIMER_0);
	DIGITAL_IO_ToggleOutput(&LEDpin);
	sensorReadings.thumb = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_thumbChannel);
	sensorReadings.index = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_indexChannel);
	sensorReadings.middle = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_middleChannel);
	sensorReadings.rp = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_rpChannel);
	MyoDataPush(&handSignals.sensorBuffer,&sensorReadings);
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

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
	  //print Values
  }
}
