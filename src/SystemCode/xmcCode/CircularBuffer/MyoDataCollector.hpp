//
//  CircularBuffer.hpp
//  CircularBuffer
//
//  Created by Hector Dominguez on 10/24/18.
//  Copyright © 2018 Hector Dominguez. All rights reserved.
//

#ifndef MyoDataCollector_hpp
#define MyoDataCollector_hpp

#include <stdio.h>

class FourTuple
{
    public:
    int thumb;
    int index;
    int middle;
    int rp;
    FourTuple() : thumb(0), index(0), middle(0), rp(0){}
    
};

//need to initialize the collection of data with SIZE readings for averages to
//make sense?
class MyoDataCollector
{
    const int SIZE;
    FourTuple * arrayPtr; //points to a dynamically allocated array of FIXED size
    int recentIdx;//most recent data points
    int oldestIdx;//oldest data points
    FourTuple averages;
    
    public:
    //CTOR
    MyoDataCollector(int size);
    //DTOR
    ~MyoDataCollector();
    
    //inserts sensor read values into the buffer of SIZE readings
    void push(FourTuple readings);
    
    //returns the "filtered" values aka the averages
    FourTuple getFilteredY();
};

bool operator==(FourTuple a, FourTuple b);

#endif /* MyoDataCollector_hpp */
