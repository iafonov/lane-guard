//
//  LaneDepartureTracker.hpp
//  Lane Guard
//
//  Created by Igor Afonov on 1/15/17.
//  Copyright © 2017 Igor Afonov. All rights reserved.
//

#ifndef LaneDepartureTracker_hpp
#define LaneDepartureTracker_hpp

#include <stdio.h>

#include "DetectedLane.hpp"

namespace LaneDetection {
    class LaneDepartureTracker {
    public:
        LaneDepartureTracker();
        
        void reset();
        void updatePosition(DetectedLane &leftLane, DetectedLane &rightLane);

        bool isDepartingLeft();
        bool isDepartingRight();
    private:
        float threshold;

        float distanceLeft;
        float distanceRight;
    };
}

#endif /* LaneDepartureTracker_hpp */
