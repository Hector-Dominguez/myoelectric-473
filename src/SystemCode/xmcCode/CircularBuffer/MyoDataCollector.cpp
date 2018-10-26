//
//  MyoDataCollector.cpp
//  MyoDataCollector
//
//  Created by Hector Dominguez on 10/24/18.
//  Copyright © 2018 Hector Dominguez. All rights reserved.
//

#include "MyoDataCollector.hpp"

using namespace std;

MyoDataCollector::MyoDataCollector(int size) :
SIZE(size), recentIdx(size-1), oldestIdx(0), averages()
{
    this->arrayPtr = new FourTuple[size];
}

MyoDataCollector::~MyoDataCollector()
{
    delete[] (this->arrayPtr);
}

void MyoDataCollector::push(FourTuple readings)
{
    //update the average of the data
    FourTuple oldestData = arrayPtr[oldestIdx];
    //thumb
    averages.thumb = averages.thumb - oldestData.thumb/SIZE + readings.thumb/SIZE;
    //index
    averages.index = averages.index - oldestData.index/SIZE + readings.index/SIZE;
    //middle
    averages.middle = averages.middle - oldestData.middle/SIZE + readings.middle/SIZE;
    //rp
    averages.rp = averages.rp - oldestData.rp/SIZE + readings.rp/SIZE;
    
    //update the data point collection
    arrayPtr[oldestIdx] = readings;
    recentIdx = oldestIdx;
    oldestIdx = (oldestIdx + 1) % SIZE;
}

FourTuple MyoDataCollector::getFilteredY()
{
    return this->averages;
}

bool operator==(FourTuple a, FourTuple b)
{
    if(a.index == b.index && a.middle == b.middle && a.thumb == b.thumb && a.rp == b.rp)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
}

//8=====>~~~~~~
