#ifndef Util_H
#define Util_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include "armadillo"

int loadImage(cv::Mat&, std::string);
void displayImage(cv::Mat&);

#endif