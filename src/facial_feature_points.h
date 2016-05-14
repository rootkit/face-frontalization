#ifndef FACIAL_FEATURE_POINTS_H
#define FACIAL_FEATURE_POINTS_H

#include <opencv2/core/core.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <string>
#include <stdio.h>


int facial_feature_detector (const std::string& img_path);
cv::Mat shape_to_np (const dlib::full_object_detection& shape);
// void disp_landmarks (const std::string& img, const std::vector <rectangle> dets, const std::vector <full_object_detection> shapes);
int convert_to_yml (std::vector <cv::Mat> landmarks);






#endif  // FACIAL_FEATURE_POINTS_H
