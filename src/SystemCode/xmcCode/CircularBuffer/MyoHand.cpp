//
//  MyoHand.cpp
//  CircularBuffer
//
//  Created by Hector Dominguez on 10/25/18.
//  Copyright © 2018 Hector Dominguez. All rights reserved.
//

#include "MyoHand.hpp"


MyoHand::MyoHand(FourTuple Channels, int windowSize) : channel(Channels),dataWindowSize(windowSize), sensorBuffer(MyoDataCollector(windowSize)) {}

//Computes yvalI for each finger
// yvalI = (filteredY - yR)/(yC - yR)
// get activation will ask MyoDataCollector for the yVal
FourTuple MyoHand::getActivationLevel()
{
    FourTuple filterReading = this->sensorBuffer.getFilteredY();
    
    this->yvalI.index = (filterReading.index - this->yR.index)/(this->yC.index - this->yR.index);
    this->yvalI.middle = (filterReading.middle - this->yR.middle)/(this->yC.middle - this->yR.middle);
    this->yvalI.thumb = (filterReading.thumb - this->yR.thumb)/(this->yC.thumb - this->yR.thumb);
    this->yvalI.rp = (filterReading.rp - this->yR.rp)/(this->yC.rp - this->yR.rp);
    return yvalI;
}

//5 seconds resting to compute yR - resting level for each channel
//5 seconds contracted to compute yC - comfortable contraction level
void MyoHand::Initialize()
{
    //5 seconds
    
    
    //5 seconds
    
}

