#pragma once
#include "facial_feature_points.h"


using namespace dlib;
using namespace std;
using namespace cv;

const string model_path = "../src/shape_predictor_68_face_landmarks.dat";

Mat shape_to_np (const full_object_detection& shape) {

    float data_list [68][2];
    for (int i=0; i<68; ++i ) {
        data_list[i][0] = shape.part (i).x ();
        data_list[i][1] = shape.part (i).y ();
    }

    Mat data = Mat (68, 2, CV_32FC1, &data_list);
    return data;
}


int facial_feature_detector (const string& img_path) {

    try {

        frontal_face_detector detector = get_frontal_face_detector ();
        shape_predictor s_predict;
        deserialize (model_path) >> s_predict;

        image_window win_a, win_b;

        array2d<rgb_pixel> img;
        load_image (img, img_path);
        pyramid_up (img);

        std::vector<rectangle> dets = detector (img);
        cout << "Number of faces detected: " << dets.size () << endl;
        std::vector<full_object_detection> shapes;

        std::vector<Mat> landmarks;
        for (unsigned long j = 0; j < dets.size (); ++j) {
            full_object_detection shape = s_predict (img, dets[j]);
            cout << "number of parts: "<< shape.num_parts () << endl;
            shapes.push_back(shape);
            landmarks.push_back (shape_to_np (shape));
        }

        convert_to_yml (landmarks);

        win_a.clear_overlay ();
        win_a.set_image (img);
        win_a.add_overlay (render_face_detections (shapes));

        dlib::array <array2d <rgb_pixel> > face_chips;
        extract_image_chips (img, get_face_chip_details(shapes), face_chips);
        win_b.set_image (tile_images (face_chips));



        // disp_landmarks (img_path, dets, shapes);

    } catch (exception& e) {
        cout << "\n[!] Exception thrown:  " << e.what () << endl;
    }

    return 0;
}


int convert_to_yml (std::vector <Mat> landmarks) {

    FileStorage fs ("../src/data/facialFeaturePoint.yml", FileStorage::WRITE);
    for (int i=0; i<landmarks.size (); ++i)
        fs <<"facialFeaturePoint" << landmarks [i];

}


// TODO: resolve the problem in compilation
// TODO: remove the code from facial_feature_detector()
/*
void disp_landmarks (const string& img, const std::vector <rectangle> dets, const std::vector <full_object_detection> shapes) {
    image_window win;
    win.clear_overlay ();
    win.set_image (img);

    for (int i=0; i<shapes.size(); ++i)
        win.add_overlay (shapes[i]);

    win.add_overlay (dets);
    // hit_enter_to_continue ();
    win.wait_until_closed ();
}
*/
