//
//  Configuration.cpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/22/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#include "Configuration.hpp"

namespace LaneDetection {
    void Configuration::setup(int frameWidth, int frameHeight, vector<Point2f> ptsSrc, vector<Point2f> ptsDst, bool inDebugMode) {
        this->frameWidth = frameWidth;
        this->frameHeight = frameHeight;
        this->inDebugMode = inDebugMode;
        this->resolution = 8;
        this->roadScale = 1.0;

        setupHomography(ptsSrc, ptsDst);
    }

    Configuration::~Configuration() {
    }

    vector<Point2f> Configuration::getOnScreenKeyPoints() {
        return onScreenKeyPoints;
    }

    vector<Point2f> Configuration::getOnRoadKeyPoints() {
        return onRoadKeyPoints;
    }

    Mat Configuration::getHomographyMatrix() {
        return homographyMatrix;
    }

    int Configuration::getFrameWidth() {
        return frameWidth;
    }

    int Configuration::getFrameHeight() {
        return frameHeight;
    }

    float Configuration::getCarWidthInches() {
        return 71 * getRoadScale(); // Civic 2016
    }

    float Configuration::getCarLeftSidePosition() {
        return getFrameWidth() / 2 - getCarWidthInches() / 2;
    }

    float Configuration::getCarRightSidePosition() {
        return getFrameWidth() / 2 + getCarWidthInches() / 2;
    }

    int Configuration::getResolution() {
        return resolution;
    }

    cv::Rect Configuration::getScanRect() {
        return scanRect;
    }

    vector<int> Configuration::getLineProbeLevels() {
        return lineProbeLevels;
    }

    bool Configuration::isInDebugMode() {
        return inDebugMode;
    }

    void Configuration::setRoadScale(float scale) {
        roadScale = scale;
    }

    float Configuration::getRoadScale() {
        return roadScale;
    }

    void Configuration::setupHomography(vector<Point2f> ptsSrc, vector<Point2f> ptsDst) {
        onScreenKeyPoints = ptsSrc;
        onRoadKeyPoints = ptsDst;

        this->scanRect = Rect(onRoadKeyPoints[1].x,
                              onRoadKeyPoints[1].y - 40,
                              onRoadKeyPoints[1].x - onRoadKeyPoints[0].x,
                              onRoadKeyPoints[3].y - onRoadKeyPoints[2].y + 30);

        int step = this->getScanRect().height / this->getResolution();

        for (int i = 0; i < this->getScanRect().height; i += step) {
            this->lineProbeLevels.push_back(getScanRect().y + i);
        }

        homographyMatrix = findHomography(ptsSrc, ptsDst);
    }
}
