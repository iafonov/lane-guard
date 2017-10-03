//
//  Configuration.hpp
//  Lane Guard
//
//  Created by Igor Afonov on 12/22/16.
//  Copyright © 2016 Igor Afonov. All rights reserved.
//

#ifndef Configuration_hpp
#define Configuration_hpp

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

namespace LaneDetection {
    class Configuration {
    public:
        virtual ~Configuration();

        static Configuration& getInstance() {
            static Configuration instance;
            return instance;
        }

        void setup(int frameWidth, int frameHeight, vector<Point2f> ptsSrc, vector<Point2f> ptsDst, bool inDebugMode = 0);

        Mat getHomographyMatrix();
        vector<Point2f> getOnScreenKeyPoints();
        vector<Point2f> getOnRoadKeyPoints();

        void setRoadScale(float scale);
        float getRoadScale();

        int getFrameWidth();
        int getFrameHeight();

        float getCarWidthInches();
        float getCarLeftSidePosition();
        float getCarRightSidePosition();

        int getResolution();

        cv::Rect getScanRect();

        vector<int> getLineProbeLevels();

        bool isInDebugMode();
    private:
        void setupHomography(vector<Point2f> ptsSrc, vector<Point2f> ptsDst);

        int frameWidth;
        int frameHeight;

        int resolution;

        bool inDebugMode;

        float roadScale;

        Mat homographyMatrix;

        cv::Rect scanRect;

        vector<int> lineProbeLevels;

        vector<Point2f> onScreenKeyPoints;
        vector<Point2f> onRoadKeyPoints;
    };
}

#endif /* Configuration_hpp */
