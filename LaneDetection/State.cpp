//
//  State.cpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/25/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#include <unistd.h>

#include "State.hpp"

namespace LaneDetection {
    State::State(EventsDelegate *eventsDelegate): eventsDelegate(eventsDelegate) {
        state = StateUnknown;
        tick = 0; lastStateSetAt = 0;
    }

    void State::handleData(DetectedLane leftLane, DetectedLane rightLane) {
        tick++;

        switch (state) {
            case StateUnknown:
                if (leftLane.isLocked() || rightLane.isLocked()) {
                    setState(StateLaneLocked);
                    eventsDelegate->laneLocked();
                }
                break;

            case StateLaneLocked:
                if (!leftLane.isLocked() && !rightLane.isLocked()) {
                    setState(StateLaneLost);
                    eventsDelegate->laneLost();
                    laneDepartureTracker.reset();
                }

                if (tick - lastStateSetAt > 60) { // 2 seconds
                    setState(StateLaneHold);
                    eventsDelegate->laneHold();
                }

                break;

            case StateLaneHold:
                if (!leftLane.isLocked() && !rightLane.isLocked()) {
                    setState(StateLaneLost);
                    eventsDelegate->laneLost();
                }

                laneDepartureTracker.updatePosition(leftLane, rightLane);

                if (laneDepartureTracker.isDepartingLeft()) {
                    setState(StateLaneDepartingLeft);
                    eventsDelegate->departingLeft();
                }

                if (laneDepartureTracker.isDepartingRight()) {
                    setState(StateLaneDepartingRight);
                    eventsDelegate->departingRight();
                }

                break;

            case StateLaneDepartingLeft:
                setState(StateLaneLost);
                break;

            case StateLaneDepartingRight:
                setState(StateLaneLost);
                break;

            case StateLaneLost:
                if (leftLane.isLocked() || rightLane.isLocked()) {
                    setState(StateLaneLocked);
                    eventsDelegate->laneLocked();
                }
                break;

            default:
                break;
        }
    }

    void State::setState(DetectionState newState) {
        state = newState;
        lastStateSetAt = tick;
    }

    DetectionState State::getCurrentState() {
        return state;
    }
}
