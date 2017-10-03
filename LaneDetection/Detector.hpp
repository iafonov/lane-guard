//
//  Detector.hpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/22/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#ifndef Detector_hpp
#define Detector_hpp

#include "opencv2/opencv.hpp"

#include "Configuration.hpp"
#include "EventsDelegate.hpp"
#include "State.hpp"
#include "DetectedLane.hpp"

using namespace cv;
using namespace std;

namespace LaneDetection {
    class Detector {
    public:
        Detector(EventsDelegate* eventsDelegate);
        virtual ~Detector();

        void processFrame(Mat &frame, int outputMode);
        void drawDebugHUD(Mat &frame);
    private:
        EventsDelegate* eventsDelegate;
        State* state;
        vector<ProbeLine*> probeLines;

        DetectedLane leftLane;
        DetectedLane rightLane;

        float findFrameMeanGrayVal(Mat &frame);
        void drawHoughLines(Mat &frame, vector<Vec4i> lines);
        Mat detectLinesHough(Mat &frame);
        void detectLanes(Mat &workFrame);
    };
}

#endif /* Detector_hpp */
