//
//  State.hpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/25/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <stdio.h>
#include "opencv2/opencv.hpp"

#include "EventsDelegate.hpp"
#include "ProbeLine.hpp"
#include "ProbePoint.hpp"
#include "DetectedLane.hpp"
#include "LaneDepartureTracker.hpp"

using namespace cv;
using namespace std;

namespace LaneDetection {
    enum DetectionState {
        StateUnknown,
        StateLaneLocked,
        StateLaneHold,
        StateLaneDepartingLeft,
        StateLaneDepartingRight,
        StateLaneLost
    };

    class State {
    public:
        State(EventsDelegate *eventsDelegate);
        void handleData(DetectedLane leftLane, DetectedLane rightLane);

        DetectionState getCurrentState();

    private:
        EventsDelegate *eventsDelegate;
        DetectionState state;
        LaneDepartureTracker laneDepartureTracker;

        void setState(DetectionState newState);

        u_long tick;
        u_long lastStateSetAt;
    };
}

#endif /* State_hpp */
