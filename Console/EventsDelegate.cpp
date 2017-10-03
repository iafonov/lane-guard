//
//  EventsDelegate.cpp
//  Lane Guard
//
//  Created by Igor Afonov on 6/27/17.
//  Copyright © 2017 Igor Afonov. All rights reserved.
//

#include "EventsDelegate.hpp"

#include "opencv2/opencv.hpp"

using namespace std;

namespace Console {
    ScreenEventsDelegate::ScreenEventsDelegate() {
        globalState = "Unknown";
        globalStateColor = Scalar(255, 255, 255);
    }

    void ScreenEventsDelegate::laneLocked() {
        globalState = "Lane In-sight";
        globalStateColor = Scalar(0, 233, 255);

        cout << "Event: Lane Locked" << endl;
    }

    void ScreenEventsDelegate::laneLost() {
        globalState = "Lane Lost";
        globalStateColor = Scalar(100, 100, 100);

        cout << "Event: Lane Lost" << endl;
    }

    void ScreenEventsDelegate::laneHold() {
        globalState = "Lane Lock";
        globalStateColor = Scalar(0, 255, 0);

        cout << "Event: Lane Hold" << endl;
    }

    void ScreenEventsDelegate::departingLeft() {
        globalState = "Departing Left";
        globalStateColor = Scalar(0, 0, 255);

        cout << "Event: Departing Left" << endl;
    }

    void ScreenEventsDelegate::departingRight() {
        globalState = "Departing Right";
        globalStateColor = Scalar(0, 0, 255);

        cout << "Event: Departing Right" << endl;
    }

    void ScreenEventsDelegate::render(Mat &frame) {
        circle(frame, Point(14, 14), 10, globalStateColor, CV_FILLED);
        putText(frame, globalState, Point(30, 22), FONT_HERSHEY_PLAIN, 1.25, globalStateColor, 1, CV_AA);
    }
}
