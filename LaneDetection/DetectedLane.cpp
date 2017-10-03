//
//  DetectedLane.cpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/29/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#include "DetectedLane.hpp"
#include "PerspectiveHelper.hpp"

namespace LaneDetection {
    DetectedLane::DetectedLane() {
    }

    DetectedLane::~DetectedLane() {
    }

    void DetectedLane::addPoint(ProbePoint* point) {
        points.push_back(point);
    }

    bool DetectedLane::isLocked() {
        vector<ProbePoint*> stablePoints = getStablePoints();

        if (stablePoints.size() > points.size() * 0.75) {
            vector<float> distances;

            for (int i = 1; i < stablePoints.size(); i++) {
                if (points[i]->isStable() && points[i-1]->isStable()) {
                    distances.push_back(findDistance(points[i - 1]->toPoint(), points[i]->toPoint()));
                }
            }
    
            Scalar mean, stddev;
            cv::meanStdDev(distances, mean, stddev);

            return (stddev[0] < mean[0] / 2);
        } else {
            return false;
        }
    }

    void DetectedLane::draw(Mat &frame) {
        if (isLocked()) {
            vector<Point2f> roadPoints = getPoints();
            vector<Point2f> screenPoints = PerspectiveHelper::convertRoadToScreen(roadPoints);

            for (int i = 0; i < screenPoints.size(); i++) {
                if (i + 1 < screenPoints.size()) {
                    line(frame, screenPoints[i], screenPoints[i + 1], Scalar(0, 255, 0), 3, CV_AA);
                }
            }
        }
    }

    vector<ProbePoint*> DetectedLane::getStablePoints() {
        vector<ProbePoint*> result;

        for (int i = 0; i < points.size(); i++) {
            if (points[i]->isStable()) {
                result.push_back(points[i]);
            }
        }

        return result;
    }

    float DetectedLane::getPosition() {
        float mean = 0;
        int count = 0;

        for (int i = 0; i < points.size(); i++) {
            if (points[i]->isStable()) {
                mean += points[i]->currentValue();
                count++;
            }
        }

        return mean / count;
    }

    float DetectedLane::findDistance(Point2i p1, Point2i p2) {
        return norm(p1 - p2);
    }

    Point2f DetectedLane::centerPoint() {
        Moments m = moments(getPoints());

        return Point(m.m10/m.m00, m.m01/m.m00);
    }

    vector<Point2f> DetectedLane::getPoints() {
        vector<Point2f> result;

        for (int i = 0; i < points.size(); i++) {
            if (points[i]->isStable()) {
                result.push_back(points[i]->toPoint());
            }
        }

        return result;
    }
}
