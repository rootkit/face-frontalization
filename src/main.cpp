#pragma once

#include <iostream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"

#include "facial_feature_points.h"
#include "frontalize.h"
#include "check_resources.h"

using namespace std;
using namespace cv;

const std::string file_name = "shape_predictor_68_face_landmarks.dat";

int usage (const char* argv[]) {
    std::cout << "[#] Usage: " << std::endl;
    std::cout << "[*] " << argv[0] << " <queryImage> <3DModelFile>" << std::endl;
    std::cout << "[*] " << argv[0] << " <queryImage> : selects predefined model" << std::endl;

    return 0;
}

int main(int argc, char const *argv[]) {
    /* code */

    if (argc != 2) {
        usage (argv);
        return -1;
    }

    string model_yml, landmarks;

    if (argc == 2)
        model_yml = "../src/3d_model/model3D.yml";
    else model_yml = argv[3];
    landmarks = "../src/data/facialFeaturePoint.yml";

    check_dlib_landmark_weights (file_name);

    Mat image = imread(argv[1]);
    Mat frontalImage;
    Mat_<float> cameraMatrix, facialFeaturePoints;
    model3D model;

    facial_feature_detector (string (argv[1]));

    readFacialFeaturePointFromYML (landmarks, facialFeaturePoints);
    read3DModelFromYML (model_yml, model);
    doCameraCalibration (model.threedee, facialFeaturePoints, model.sizeU, model.outA, cameraMatrix);
    frontalizeWithoutSymmetry (image, cameraMatrix, model.refU, model.sizeU, frontalImage);

    imshow("image", image);
    imshow("frontal", frontalImage);
    waitKey();

    imwrite("image.png", image);
    imwrite("frontal.png", frontalImage);

    return 0;
}
