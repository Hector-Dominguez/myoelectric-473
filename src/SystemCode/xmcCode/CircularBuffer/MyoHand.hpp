//
//  MyoHand.hpp
//  CircularBuffer
//
//  Created by Hector Dominguez on 10/25/18.
//  Copyright © 2018 Hector Dominguez. All rights reserved.
//

#ifndef MyoHand_hpp
#define MyoHand_hpp

#include <stdio.h>
#include "MyoDataCollector.hpp"

class MyoHand {
    MyoDataCollector sensorBuffer;
    int dataWindowSize;
    FourTuple channel;
    FourTuple yvalI;//scaled, filtered, conditioned Muscle Activation Value
    FourTuple yR; // resting average
    FourTuple yC; // comfortable contraction average
    public:
    //CTOR
    MyoHand(FourTuple Channels, int windowSize);
    
    //Computes yvalI for each finger
    // yvalI = (filteredY - yR)/(yC - yR)
    // get activation will ask MyoDataCollector for the yVal
    FourTuple getActivationLevel();
    
    //5 seconds resting to compute yR - resting level for each channel
    //5 seconds contracted to compute yC - comfortable contraction level
    void Initialize();
};

#endif /* MyoHand_hpp */
