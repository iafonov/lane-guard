//
//  ProbePoint.cpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/22/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#include "ProbePoint.hpp"
#include "PerspectiveHelper.hpp"

#include <algorithm>

namespace LaneDetection {
    ProbePoint::ProbePoint(size_t maxSize, int levelY) {
        this->maxSize = maxSize;
        this->levelY = levelY;
        this->confidence = 0;
    }

    ProbePoint::~ProbePoint() {
    }

    float ProbePoint::getConfidence() {
        return confidence;
    }

    void ProbePoint::debugDraw(Mat &frame) {
        int frameY = levelY;

        Scalar color = Scalar(100, 100, 100);

        if (isStable()) {
            color = Scalar(0, 255, 0);
        }

        if (buffer.size() > 0) {
            circle(frame, Point(currentValue(), frameY), 3, color, CV_FILLED);
        }
    }

    int ProbePoint::currentValue() {
        int value = 0;
        int count = 0;

        if (size() > 1) {
            for (int i = 0; i < size(); i++) {
                value += buffer[i] * pow(i, 4);
                count += pow(i, 4);
            }

            return value / count;
        } else {
            return buffer[0];
        }
    }

    void ProbePoint::updateValue(int value) {
        if (value == Configuration::getInstance().getFrameWidth() / 2 ||
              PerspectiveHelper::convertRoadToScreen(Point2f(value, levelY)).x < 5 ||
              PerspectiveHelper::convertRoadToScreen(Point2f(value, levelY)).x > (Configuration::getInstance().getFrameWidth() - 5) ) {
            decConfidence();
            return;
        }

        if (size() == 0) {
            addToBuffer(value);
        } else if (size() == 1) {
            if (abs(buffer[0] - value) < 5) {
                addToBuffer(value);
            } else {
                removeFromBuffer();
            }
        } else {
            if (abs(mean() - value) <= 5 * stddev()) {
                addToBuffer(value);
                incConfidence();
            } else {
                decConfidence();
            }
        }

        if (buffer.size() > this->maxSize) {
            buffer.erase(buffer.begin());
        }
    }

    bool ProbePoint::isStable() {
        return (confidence > 5 && std::abs(stddev()) < mean() / 10);
    }

    Point2i ProbePoint::toPoint() {
        return Point2i(currentValue(), levelY);
    }

    void ProbePoint::removeFromBuffer() {
        buffer.erase(buffer.begin());
    }

    void ProbePoint::addToBuffer(int value) {
        buffer.push_back(value);
    }

    float ProbePoint::maxConfidence() {
        return 10;
    }

    void ProbePoint::incConfidence() {
        if (confidence < maxConfidence()) {
            confidence+=3.5;
        }

        confidence = std::min(confidence, maxConfidence());
    }

    void ProbePoint::decConfidence() {
        if (isStable()) {
            confidence-=0.2;
        } else {
            buffer.clear();
            confidence = 0;
        }
    }

    float ProbePoint::mean() {
        if (size() > 1) {
            Scalar mean, stddev;
            cv::meanStdDev(buffer, mean, stddev);

            return mean[0];
        } else {
            return 0.0;
        }
    }

    float ProbePoint::stddev() {
        if (size() > 1) {
            Scalar mean, stddev;
            cv::meanStdDev(buffer, mean, stddev);

            return stddev[0];
        } else {
            return 0.0;
        }
    }

    size_t ProbePoint::size() {
        return buffer.size();
    }
}
