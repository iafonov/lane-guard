//
//  TestBed.cpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/22/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#include "opencv2/opencv.hpp"

#include "LaneDetection/Detector.hpp"
#include "Console/EventsDelegate.hpp"

using namespace cv;
using namespace std;

int currentMode = 0;

void mainWindowCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        currentMode++;
        if (currentMode > 2) {
            currentMode = 0;
        }
    }
}

int main(int argc, char** argv) {
    namedWindow("video", 1);
    setMouseCallback("video", mainWindowCallback, NULL);

    // Screen points - points on screen (pixels)
    vector<Point2f> ptsSrc;

    // Left
    ptsSrc.push_back(Point2f(123, 205));
    ptsSrc.push_back(Point2f(176, 150));

    // Right
    ptsSrc.push_back(Point2f(276, 150));
    ptsSrc.push_back(Point2f(332, 205));

    // On-Road points - points on road (inches)
    vector<Point2f> ptsDst;

    // Left
    ptsDst.push_back(Point2f(240 + -45, 203));
    ptsDst.push_back(Point2f(240 + -45, 98));

    // Right
    ptsDst.push_back(Point2f(240 + 45, 98));
    ptsDst.push_back(Point2f(240 + 45, 203));
    
    LaneDetection::Configuration::getInstance().setup(480, 270, ptsSrc, ptsDst, 1);

    Console::ScreenEventsDelegate *screenEventsDelegate = new Console::ScreenEventsDelegate();

    LaneDetection::Detector* detector = new LaneDetection::Detector(screenEventsDelegate);

    VideoCapture cap(argv[1]);
    for(;;)
    {
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            break;
        }

        detector->processFrame(frame, currentMode);
        screenEventsDelegate->render(frame);

        imshow("video", frame);

        if (waitKey(25) >= 0) break;
    }

    delete detector;
    delete screenEventsDelegate;

    return 0;
}
