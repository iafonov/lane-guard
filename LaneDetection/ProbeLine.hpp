//
//  ProbeLine.hpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/28/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#ifndef ProbeLine_hpp
#define ProbeLine_hpp

#include <stdio.h>
#include "opencv2/opencv.hpp"

#include "ProbePoint.hpp"

using namespace cv;
using namespace std;

namespace LaneDetection {
    class ProbeLine {
    public:
        ProbeLine(int y);
        ~ProbeLine();

        int getY();
        void scan(Mat &frame);
        void debugDraw(Mat &frame);

        ProbePoint* getLeftProbePointRef();
        ProbePoint* getRightProbePointRef();
    private:
        int y;

        ProbePoint* left;
        ProbePoint* right;
    };
}

#endif /* ProbeLine_hpp */
