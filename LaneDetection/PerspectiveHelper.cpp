//
//  PerspectiveHelper.cpp
//  Lane Guard
//
//  Created by Igor Afonov on 1/12/17.
//  Copyright © 2017 Igor Afonov. All rights reserved.
//

#include "PerspectiveHelper.hpp"
#include "Configuration.hpp"

namespace LaneDetection {
    Point2f PerspectiveHelper::convertRoadToScreen(Point2f srcPoint) {
        vector<Point2f> src;
        vector<Point2f> dst;
        
        src.push_back(srcPoint);

        perspectiveTransform(src, dst, Configuration::getInstance().getHomographyMatrix().inv());

        return dst[0];
    }

    vector<Point2f> PerspectiveHelper::convertRoadToScreen(vector<Point2f> srcPoints) {
        vector<Point2f> dst;

        perspectiveTransform(srcPoints, dst, Configuration::getInstance().getHomographyMatrix().inv());

        return dst;

    }
}
