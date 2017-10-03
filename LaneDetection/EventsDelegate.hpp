//
//  EventsDelegate.hpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/22/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#ifndef EventsDelegate_hpp
#define EventsDelegate_hpp

#include <stdio.h>

namespace LaneDetection {
    class EventsDelegate {
    public:
        virtual void laneLocked() = 0;
        virtual void laneHold() = 0;
        virtual void laneLost() = 0;

        virtual void departingLeft() = 0;
        virtual void departingRight() = 0;
    };
}

#endif /* EventsDelegate_hpp */
