//
//  MyoDataCollector.c
//  MyoSensor
//
//  Created by Hector Dominguez on 10/26/18.
//  Copyright © 2018 Hector Dominguez. All rights reserved.
//

#include "MyoDataCollector.h"


void MyoDataCollectorINIT(struct MyoDataCollector * myoDataPtr)
{
    struct FourTuple zeroVals;
    zeroVals.index = 0;
    zeroVals.middle = 0;
    zeroVals.thumb = 0;
    zeroVals.rp = 0;
    
    for(int i = 0; i < DataWindow; i++)
    {
        myoDataPtr->arrayPtr[i] = zeroVals;
    }
    myoDataPtr->oldestIdx = 0;
    myoDataPtr->recentIdx = DataWindow - 1;
    myoDataPtr->SIZE = DataWindow;
    myoDataPtr->averages = zeroVals;
 
};


//inserts sensor read values into the buffer of SIZE readings
void MyoDataPush(struct MyoDataCollector * myoDataPtr, struct FourTuple * readingsPtr)
{
    //update the average of the data
    struct FourTuple oldestData = myoDataPtr->arrayPtr[myoDataPtr->oldestIdx];
    
    struct FourTuple averages = myoDataPtr->averages;
    
    int SIZE = myoDataPtr->SIZE;
    
    //thumb
    averages.thumb = averages.thumb - oldestData.thumb/SIZE + readingsPtr->thumb/SIZE;
    //index
    averages.index = averages.index - oldestData.index/SIZE + readingsPtr->index/SIZE;
    //middle
    averages.middle = averages.middle - oldestData.middle/SIZE + readingsPtr->middle/SIZE;
    //rp
    averages.rp = averages.rp - oldestData.rp/SIZE + readingsPtr->rp/SIZE;
    
    //update the averages in the MyoDataCollector
    myoDataPtr->averages = averages;
    
    //update the data point collection
    myoDataPtr->arrayPtr[myoDataPtr->oldestIdx] = *readingsPtr;
    myoDataPtr->recentIdx = myoDataPtr->oldestIdx;
    myoDataPtr->oldestIdx = (myoDataPtr->oldestIdx + 1) % SIZE;
}


int CompareFourTuple(struct FourTuple * aPtr, struct FourTuple * bPtr)
{
    if (aPtr->index == bPtr->index && aPtr->thumb == bPtr->thumb && aPtr->middle == bPtr->middle && aPtr->rp == bPtr->rp)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

//8=====>~~~~~~
