//
//  ProbePoint.hpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/22/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#ifndef ProbePoint_hpp
#define ProbePoint_hpp

#include <stdio.h>
#include "opencv2/opencv.hpp"

#include "Configuration.hpp"

using namespace cv;
using namespace std;

namespace LaneDetection {
    class ProbePoint {
    public:
        ProbePoint(size_t maxSize, int levelY);
        ~ProbePoint();

        void updateValue(int value);
        int currentValue();

        bool isStable();

        void debugDraw(Mat &frame);

        Point2i toPoint();
    private:
        vector<int> buffer;
        float confidence;
        int levelY;

        size_t maxSize;
        int valueIndex;
        size_t currentSize;

        void addToBuffer(int value);
        void removeFromBuffer();
        size_t size();

        float mean();
        float stddev();

        float maxConfidence();
        void incConfidence();
        void decConfidence();
        float getConfidence();
    };
}
#endif /* ProbePoint_hpp */
