//
//  DetectedLane.hpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/29/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#ifndef DetectedLane_hpp
#define DetectedLane_hpp

#include <stdio.h>
#include "ProbePoint.hpp"

#include "opencv2/opencv.hpp"

namespace LaneDetection {
    class DetectedLane {
    public:
        DetectedLane();
        ~DetectedLane();

        void addPoint(ProbePoint* point);

        bool isLocked();
        float getPosition();

        vector<Point2f> getPoints();
        Point2f centerPoint();

        void draw(Mat &frame);
    private:
        vector<ProbePoint*> points;

        vector<ProbePoint*> getStablePoints();
        float findDistance(Point2i p1, Point2i p2);
    };
}

#endif /* DetectedLane_hpp */
