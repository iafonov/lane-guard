//
//  Detector.cpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/22/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#include "Detector.hpp"
#include <unistd.h>
#include <algorithm>

namespace LaneDetection {
    Detector::Detector(EventsDelegate* eventsDelegate): eventsDelegate(eventsDelegate) {
        state = new State(eventsDelegate);

        for (int i = 0; i < Configuration::getInstance().getLineProbeLevels().size(); i++) {
            ProbeLine* probeLine = new ProbeLine(Configuration::getInstance().getLineProbeLevels()[i]);

            leftLane.addPoint(probeLine->getLeftProbePointRef());
            rightLane.addPoint(probeLine->getRightProbePointRef());

            probeLines.push_back(probeLine);
        }
    }

    Detector::~Detector() {
        delete state;
    }

    void Detector::processFrame(Mat &frame, int outputMode) {
        Configuration config = Configuration::getInstance();

        Mat warpedFrame = Mat::zeros(frame.size(), CV_8UC3);
        warpPerspective(frame, warpedFrame, config.getHomographyMatrix(), frame.size());

        Mat workFrame = detectLinesHough(warpedFrame);

        detectLanes(workFrame);

        state->handleData(leftLane, rightLane);

        if (outputMode == 0) {
            drawDebugHUD(frame);
        } else if (outputMode == 1) {
            rectangle(warpedFrame, config.getScanRect(), Scalar(0, 0, 255), 1);

            for (int i = 0; i < probeLines.size(); i++) {
                probeLines[i]->debugDraw(warpedFrame);
            }

            for (int i = 0; i < config.getOnRoadKeyPoints().size(); i++) {
                circle(warpedFrame, config.getOnRoadKeyPoints()[i], 3, Scalar(255, 255, 255), CV_FILLED);
            }

            line(warpedFrame, Point(config.getCarLeftSidePosition(), 0), Point(config.getCarLeftSidePosition(), config.getFrameHeight()), Scalar(100, 100, 100), 2);
            line(warpedFrame, Point(config.getCarRightSidePosition(), 0), Point(config.getCarRightSidePosition(), config.getFrameHeight()), Scalar(100, 100, 100), 2);

            frame = warpedFrame;
        } else if (outputMode == 2) {
            Mat hudFrame = Mat::zeros(frame.size(), CV_8UC3);

            if (leftLane.isLocked()) {
                rectangle(hudFrame, Point(leftLane.getPosition() - 3, 0), Point(leftLane.getPosition() + 3, frame.size().height), Scalar(33, 211, 126), CV_FILLED);
            } else {
                rectangle(hudFrame, Point(leftLane.getPosition() - 2, 0), Point(leftLane.getPosition() + 3, frame.size().height), Scalar(130, 130, 130), 1);
            }

            if (rightLane.isLocked()) {
                rectangle(hudFrame, Point(rightLane.getPosition() - 3, 0), Point(rightLane.getPosition() + 3, frame.size().height), Scalar(33, 211, 126), CV_FILLED);
            } else {
                rectangle(hudFrame, Point(leftLane.getPosition() - 3, 0), Point(leftLane.getPosition() + 3, frame.size().height), Scalar(130, 130 ,130), 1);
            }

            line(hudFrame, Point(config.getCarLeftSidePosition(), 0), Point(config.getCarLeftSidePosition(), config.getFrameHeight()), Scalar(2, 18, 200), 2);
            line(hudFrame, Point(config.getCarRightSidePosition(), 0), Point(config.getCarRightSidePosition(), config.getFrameHeight()), Scalar(2, 18, 200), 2);

            for (int i = 0; i < Configuration::getInstance().getOnRoadKeyPoints().size(); i++) {
                circle(hudFrame, Configuration::getInstance().getOnRoadKeyPoints()[i], 1, Scalar(255, 255, 255), CV_FILLED);
            }

            circle(hudFrame, Point(10,10), 5, Scalar(255, 255, 255), CV_FILLED);

            frame = hudFrame;
        }
    }

    void Detector::detectLanes(Mat &workFrame) {
        for (int i = 0; i < probeLines.size(); i++) {
            probeLines[i]->scan(workFrame);
        }
    }

    float Detector::findFrameMeanGrayVal(Mat &frame) {
        return std::max(mean(frame).val[0], 60.0);
    }

    void Detector::drawHoughLines(Mat &frame, vector<Vec4i> lines) {
        for(size_t i = 0; i < lines.size(); i++) {
            Vec4i l = lines[i];
            float angle = atan2(l[3] - l[1], l[2] - l[0]) * 180.0 / CV_PI;

            if (angle < -10 || angle > 10) {
                line(frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 1, 4);
            }
        }
    }

    Mat Detector::detectLinesHough(Mat &frame) {
        Mat workFrame(frame.size(), CV_8U);
        Mat houghLinesFrame = Mat::zeros(frame.size(), CV_8U);

        cvtColor(frame, workFrame, CV_BGR2GRAY);

        int blurSize = ceil(4 * Configuration::getInstance().getRoadScale());
        blur(workFrame, workFrame, Size(blurSize, blurSize));

        float cannyTreshold = findFrameMeanGrayVal(workFrame);
        Canny(workFrame, workFrame, cannyTreshold * 0.66, cannyTreshold * 1.33);

        vector<Vec4i> lines;
        HoughLinesP(workFrame, lines, 1, CV_PI/180, 10, 10, 10);

        drawHoughLines(houghLinesFrame, lines);

        return houghLinesFrame;
    }

    void Detector::drawDebugHUD(Mat &frame) {
        Configuration config = Configuration::getInstance();
        for (int i = 0; i < config.getOnScreenKeyPoints().size(); i++) {
            circle(frame, config.getOnScreenKeyPoints()[i], 1, Scalar(255, 255, 255), CV_FILLED);
        }

        line(frame, Point(0, config.getFrameHeight() / 2), Point(config.getFrameWidth(), config.getFrameHeight() / 2), Scalar(0, 150, 0), 1);
        line(frame, Point(config.getFrameWidth() / 2, 0), Point(config.getFrameWidth() / 2, config.getFrameHeight()), Scalar(0, 150, 0), 1);

        rightLane.draw(frame);
        leftLane.draw(frame);
    }
};
