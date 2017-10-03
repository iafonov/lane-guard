//
//  ProbeLine.cpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/28/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#include "ProbeLine.hpp"

namespace LaneDetection {
    ProbeLine::ProbeLine(int y) {
        this->y = y;
        this->left = new ProbePoint(30, y);
        this->right = new ProbePoint(30, y);
    }

    ProbeLine::~ProbeLine() {
        delete left;
        delete right;
    }

    int ProbeLine::getY() {
        return y;
    }

    ProbePoint* ProbeLine::getLeftProbePointRef() {
        return left;
    }

    ProbePoint* ProbeLine::getRightProbePointRef() {
        return right;
    }

    void ProbeLine::scan(Mat &frame) {
        int centerX = Configuration::getInstance().getFrameWidth() / 2;

        int distLeft = 0;
        for (int x = centerX; x > 0; x--) {
            if (frame.at<uchar>(Point(x, y)) > 0) {
                distLeft = centerX - x;
                break;
            }
        }

        left->updateValue(centerX - distLeft);

        int distRight = 0;
        for (int x = centerX; x < frame.size().width; x++) {
            if (frame.at<uchar>(Point(x, y)) > 0) {
                distRight = x - centerX;
                break;
            }
        }

        right->updateValue(centerX + distRight);
    }

    void ProbeLine::debugDraw(Mat &frame) {
        line(frame, Point(0, y), Point(Configuration::getInstance().getFrameWidth(), y), Scalar(100, 100, 100));

        left->debugDraw(frame);
        right->debugDraw(frame);
    }
}
