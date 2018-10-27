//
//  main.c
//  MyoSensor
//
//  Created by Hector Dominguez on 10/26/18.
//  Copyright © 2018 Hector Dominguez. All rights reserved.
//

#include <stdio.h>
#include "MyoDataCollector.h"
#include "MyoHand.h"
#include <assert.h>



void test1(void);
void test2(void);
void test3(void);
void test4(void);

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}

void test1(void)
{
    struct MyoDataCollector collector;
    //collector should start with all 0s and 5 elements
    
    MyoDataCollectorINIT(&collector);
    
    //read 7 elements
    struct FourTuple sensorRead;
    struct FourTuple averageVals;
    
    sensorRead.thumb = 10;
    sensorRead.index = 10;
    sensorRead.middle = 10;
    sensorRead.rp = 10;
    
    averageVals.thumb = 10/DataWindow;
    averageVals.index = 10/DataWindow;;
    averageVals.middle = 10/DataWindow;;
    averageVals.rp = 10/DataWindow;
    
    MyoDataPush(&collector, &sensorRead);
    assert(CompareFourTuple(&(collector.averages), &averageVals));
    
    sensorRead.thumb = 20;
    sensorRead.index = 20;
    sensorRead.middle = 20;
    sensorRead.rp = 20;
    
    averageVals.thumb = 10/DataWindow + 20/DataWindow;
    averageVals.index = 10/DataWindow + 20/DataWindow;
    averageVals.middle = 10/DataWindow + 20/DataWindow;
    averageVals.rp = 10/DataWindow + 20/DataWindow;
    
    MyoDataPush(&collector, &sensorRead);
    assert(CompareFourTuple(&(collector.averages), &averageVals));
    
    
    sensorRead.thumb = 30;
    sensorRead.index = 30;
    sensorRead.middle = 30;
    sensorRead.rp = 30;
    
    averageVals.thumb = 10/DataWindow + 20/DataWindow + 30/DataWindow;
    averageVals.index = 10/DataWindow + 20/DataWindow + 30/DataWindow;
    averageVals.middle = 10/DataWindow + 20/DataWindow + 30/DataWindow;
    averageVals.rp = 10/DataWindow + 20/DataWindow + 30/DataWindow;
    
    MyoDataPush(&collector, &sensorRead);
    assert(CompareFourTuple(&(collector.averages), &averageVals));
    
    sensorRead.thumb = 35;
    sensorRead.index = 35;
    sensorRead.middle = 35;
    sensorRead.rp = 35;
    
    averageVals.thumb = 10/DataWindow + 20/DataWindow + 30/DataWindow + 35/DataWindow;
    averageVals.index = 10/DataWindow + 20/DataWindow + 30/DataWindow + 35/DataWindow;
    averageVals.middle = 10/DataWindow + 20/DataWindow + 30/DataWindow + 35/DataWindow;
    averageVals.rp = 10/DataWindow + 20/DataWindow + 30/DataWindow + 35/DataWindow;
    
    MyoDataPush(&collector, &sensorRead);
    assert(CompareFourTuple(&(collector.averages), &averageVals));
    
    
    sensorRead.thumb = 40;
    sensorRead.index = 40;
    sensorRead.middle = 40;
    sensorRead.rp = 40;
    
    averageVals.thumb = 10/DataWindow + 20/DataWindow + 30/DataWindow + 35/DataWindow + 40/DataWindow;
    averageVals.index = 10/DataWindow + 20/DataWindow + 30/DataWindow + 35/DataWindow + 40/DataWindow;
    averageVals.middle = 10/DataWindow + 20/DataWindow + 30/DataWindow + 35/DataWindow + 40/DataWindow;
    averageVals.rp = 10/DataWindow + 20/DataWindow + 30/DataWindow + 35/DataWindow + 40/DataWindow;
    
    MyoDataPush(&collector, &sensorRead);
    assert(CompareFourTuple(&(collector.averages), &averageVals));
    
    
    sensorRead.thumb = 48;
    sensorRead.index = 48;
    sensorRead.middle = 48;
    sensorRead.rp = 48;
    
    averageVals.thumb = 20/DataWindow + 30/DataWindow + 35/DataWindow + 40/DataWindow + 48/DataWindow;
    averageVals.index = 20/DataWindow + 30/DataWindow + 35/DataWindow + 40/DataWindow + 48/DataWindow;
    averageVals.middle = 20/DataWindow + 30/DataWindow + 35/DataWindow + 40/DataWindow + 48/DataWindow;
    averageVals.rp = 20/DataWindow + 30/DataWindow + 35/DataWindow + 40/DataWindow + 48/DataWindow;
    
    MyoDataPush(&collector, &sensorRead);
    assert(CompareFourTuple(&(collector.averages), &averageVals));
    
    
    
    /*
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
     */
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
