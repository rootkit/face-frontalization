#ifndef FRONTALIZE_H
#define FRONTALIZE_H


#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <opencv2/core/core.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"
#include "calib/calib.h"

using namespace std;
using namespace cv;


typedef struct model3D
{
    Mat_<float> refU;              // mapping between reference image and 3d model (Nx3)
    Size sizeU;                    // size of refU, just for easy access
    Mat_<float> refXY;             // detected facial points in reference image
    Mat_<float> threedee;          // matching points of refXY in 3D model
    Mat_<float> outA;              // intrinsic matrix of camera
} model3D, *model3DP;


#ifndef DEBUGMSG
#define DEBUGMSG(msg) cout << "line: " <<__LINE__ \
    << ", file: " << __FILE__ \
    << ", message: " << msg << endl;
#endif  // DEBUGMSG

void readFacialFeaturePointFromYML(const std::string& fileName,
                                   Mat_<float>& facialFeaturePoint);


void read3DModelFromYML(const std::string & fileName,
                        model3D& model);


void readCameraMatrixFromYML(const std::string& fileName,
                             Mat_<float>& cameraMatrix);

void readMatFromFile(const string& fileName, Mat_<float>& m);


template <typename T>
bool equal(const T& x, const T& y)
{
    if(x-y < 1e-5 && x-y > 1e-5)
        return true;
    else
        return false;
}




void frontalizeWithoutSymmetry(const Mat& image,
                               const Mat_<float>& cameraMatrix,
                               const Mat_<float>& refU,
                               const Size &refSize,
                               Mat &frontalImage,
                               Mat_<float> &projection_ = *(new Mat_<float>()),
                               vector<int> &indexFrontal_ = *(new vector<int>())
                           );

void frontalizeWithSoftSymmetry(const Mat& image,
                                const Mat_<float>& cameraMatrix,
                                const Mat_<float>& refU,
                                const Size &refSize,
                                const Mat_<float>& eyeMask,
                                Mat& frontalImage
                            );

void bilinearInterp(const Mat& src,
                    const Mat_<float>& pos,
                    const vector<int> &indexFrontal,
                    const Size dstSize,
                    Mat& dst
                );

void doCameraCalibration(const Mat_<float>& Points3D,
                        const Mat_<float>& Points2D,
                        const Size imgSize,
                        const Mat_<float> &intrinsicMatrix, Mat_<float> &cameraMatrix
                    );


#endif  // FRONTALIZE_H
