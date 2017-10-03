//
//  PerspectiveHelper.hpp
//  Lane Guard
//
//  Created by Igor Afonov on 1/12/17.
//  Copyright © 2017 Igor Afonov. All rights reserved.
//

#ifndef PerspectiveHelper_hpp
#define PerspectiveHelper_hpp

#include <stdio.h>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

namespace LaneDetection {
    class PerspectiveHelper {
    public:
        static Point2f convertRoadToScreen(Point2f srcPoint);
        static vector<Point2f> convertRoadToScreen(vector<Point2f> srcPoints);
    };
}

#endif /* PerspectiveHelper_hpp */
