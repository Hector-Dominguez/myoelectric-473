//
//  MyoHand.h
//  MyoSensor
//
//  Created by Hector Dominguez on 10/27/18.
//  Copyright © 2018 Hector Dominguez. All rights reserved.
//

#ifndef MyoHand_h
#define MyoHand_h

#include <stdio.h>
#include "MyoDataCollector.h"

struct MyoHand {
    struct MyoDataCollector sensorBuffer;
    struct FourTuple yvalI;//scaled, filtered, conditioned Muscle Activation Value
    struct FourTuple yR; // resting average
    struct FourTuple yC; // comfortable contraction average
};

//Initializer
void MyoHandINIT(struct MyoHand * myohandPtr);

//Computes yvalI for each finger
// yvalI = (filteredY - yR)/(yC - yR)
// get activation will ask MyoDataCollector for the yVal
struct FourTuple GetActivationLevels(struct MyoHand * myohandPtr);

//5 seconds resting to compute yR - resting level for each channel
//5 seconds contracted to compute yC - comfortable contraction level
void InitializeLevels(struct MyoHand * myohandPtr);


#endif /* MyoHand_h */


