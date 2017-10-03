//
//  LaneDepartureTracker.cpp
//  Lane Guard
//
//  Created by Igor Afonov on 1/15/17.
//  Copyright © 2017 Igor Afonov. All rights reserved.
//

#include "LaneDepartureTracker.hpp"

namespace LaneDetection {
    LaneDepartureTracker::LaneDepartureTracker() {
        threshold = 0;
        reset();
    }
    
    void LaneDepartureTracker::reset() {
        distanceLeft = 0;
        distanceRight = 0;
    }

    void LaneDepartureTracker::updatePosition(DetectedLane &leftLane, DetectedLane &rightLane) {
        distanceLeft = Configuration::getInstance().getCarLeftSidePosition() - leftLane.getPosition();
        distanceRight = rightLane.getPosition() - Configuration::getInstance().getCarRightSidePosition();
    }

    bool LaneDepartureTracker::isDepartingLeft() {
        return distanceLeft < 15;
    }

    bool LaneDepartureTracker::isDepartingRight() {
        return distanceRight < 15;
    }
}
