//
//  EventsDelegate.hpp
//  Lane Guard
//
//  Created by Igor Afonov on 6/27/17.
//  Copyright © 2017 Igor Afonov. All rights reserved.
//

#ifndef ConsoleEventsDelegate_hpp
#define ConsoleEventsDelegate_hpp

#include "opencv2/opencv.hpp"
#include "../LaneDetection/EventsDelegate.hpp"

using namespace cv;
using namespace std;

namespace Console {
    class ScreenEventsDelegate: public LaneDetection::EventsDelegate {
    public:
        ScreenEventsDelegate();

        virtual void laneLocked();
        virtual void laneHold();
        virtual void laneLost();

        virtual void departingLeft();
        virtual void departingRight();

        void render(Mat &frame);
    private:
        string globalState;
        Scalar globalStateColor;
    };
}

#endif /* ConsoleEventsDelegate_hpp */
