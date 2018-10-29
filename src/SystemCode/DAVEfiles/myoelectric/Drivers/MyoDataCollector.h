//
//  MyoDataCollector.h
//  MyoSensor
//
//  Created by Hector Dominguez on 10/26/18.
//  Copyright © 2018 Hector Dominguez. All rights reserved.
//

#ifndef MyoDataCollector_h
#define MyoDataCollector_h

#include <stdio.h>

#define DataWindow 100

struct FourTuple {
    int thumb;
    int index;
    int middle;
    int rp;
};


//need to initialize the collection of data with SIZE readings for averages to
//make sense?
struct MyoDataCollector {
    int SIZE;
    struct FourTuple arrayPtr[DataWindow]; //points to a dynamically allocated array of FIXED size
    int recentIdx;//most recent data points
    int oldestIdx;//oldest data points
    struct FourTuple averages;//filtered Yval
    
};
//Initializer
void MyoDataCollectorINIT(struct MyoDataCollector * myoDataPtr);



//inserts sensor read values into the buffer of SIZE readings
void MyoDataPush(struct MyoDataCollector * myoDataPtr, struct FourTuple * readingsPtr);

int CompareFourTuple(struct FourTuple * aPtr, struct FourTuple * bPtr);

#endif /* MyoDataCollector_h */
