//
//  MyoHand.c
//  MyoSensor
//
//  Created by Hector Dominguez on 10/27/18.
//  Copyright © 2018 Hector Dominguez. All rights reserved.
//

#include "MyoHand.h"



//Initializer
void MyoHandINIT(struct MyoHand * myohandPtr,struct FourTuple Channels)
{
    struct FourTuple zeroVals;
    zeroVals.index = 0;
    zeroVals.middle = 0;
    zeroVals.thumb = 0;
    zeroVals.rp = 0;
    
    myohandPtr->channel = Channels;
    myohandPtr->yvalI = zeroVals;
    myohandPtr->yR = zeroVals;
    myohandPtr->yC = zeroVals;
}

//Computes yvalI for each finger
// yvalI = (filteredY - yR)/(yC - yR)
// get activation will ask MyoDataCollector for the yVal
struct FourTuple GetActivationLevels(struct MyoHand * myohandPtr)
{
    struct FourTuple filterReading = myohandPtr->sensorBuffer.averages;
    struct FourTuple yRs = myohandPtr->yR;
    struct FourTuple yCs = myohandPtr->yC;
    
    myohandPtr->yvalI.index = (filterReading.index - yRs.index)/(yCs.index - yRs.index);
    myohandPtr->yvalI.middle = (filterReading.middle - yRs.middle)/(yCs.middle - yRs.middle);
    myohandPtr->yvalI.thumb = (filterReading.thumb - yRs.thumb)/(yCs.thumb - yRs.thumb);
    myohandPtr->yvalI.rp = (filterReading.rp - yRs.rp)/(yCs.rp - yRs.rp);
    
    return myohandPtr->yvalI;
}

//5 seconds resting to compute yR - resting level for each channel
//5 seconds contracted to compute yC - comfortable contraction level
void InitializeLevels(struct MyoHand * myohandPtr)
{
    //5 seconds
    
    
    //5 seconds
    
}
