//
//  MyoDataCollectTests.cpp
//  CircularBuffer
//
//  Created by Hector Dominguez on 10/24/18.
//  Copyright © 2018 Hector Dominguez. All rights reserved.
//

#include <stdio.h>
#include "MyoDataCollector.hpp"
#include <assert.h>

using namespace std;

void test1();
void test2();
void test3();
void test4();

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}

void test1()
{
    MyoDataCollector collector(7);
    //collector should start with all 0s and 5 elements
    //read 7 elements
    FourTuple sensorRead;
    sensorRead.thumb = 10;
    FourTuple averageVals;
    averageVals.thumb = 10/7;
    
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    sensorRead.thumb = 20;
    averageVals.thumb = (10/7)+(20)/7;
    
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    sensorRead.thumb = 25;
    averageVals.thumb = 10/7+20/7+25/7;
    
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    sensorRead.thumb = 30;
    averageVals.thumb = 10/7+20/7+25/7+30/7;
    
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    sensorRead.thumb = 35;
    averageVals.thumb = 10/7+20/7+25/7+30/7+35/7;
    
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    sensorRead.thumb = 40;
    averageVals.thumb = 10/7+20/7+25/7+30/7+35/7+40/7;
    
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    sensorRead.thumb = 48;
    averageVals.thumb = 10/7+20/7+25/7+30/7+35/7+40/7+48/7;
    
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    
    sensorRead.thumb = 48;
    averageVals.thumb = 48/7+20/7+25/7+30/7+35/7+40/7+48/7;
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    
    sensorRead.thumb = 100;
    averageVals.thumb = 48/7+100/7+25/7+30/7+35/7+40/7+48/7;
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    
    sensorRead.thumb = 100;
    averageVals.thumb = 48/7+100/7+100/7+30/7+35/7+40/7+48/7;
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    
    sensorRead.thumb = 100;
    averageVals.thumb = 48/7+100/7+100/7+100/7+35/7+40/7+48/7;
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    
    sensorRead.thumb = 100;
    averageVals.thumb = 48/7+100/7+100/7+100/7+100/7+40/7+48/7;
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    
    sensorRead.thumb = 100;
    averageVals.thumb = 48/7+100/7+100/7+100/7+100/7+100/7+48/7;
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    
    sensorRead.thumb = 100;
    averageVals.thumb = 48/7+100/7+100/7+100/7+100/7+100/7+100/7;
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
    
    sensorRead.thumb = 100;
    averageVals.thumb = 100/7+100/7+100/7+100/7+100/7+100/7+100/7;
    collector.push(sensorRead);
    assert(collector.getFilteredY() == averageVals);
}


void test2()
{
    
}

void test3()
{
    
}

void test4()
{
    
}
