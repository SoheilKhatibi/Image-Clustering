#ifndef ABSTRACTIMAGECLUSTERING_H
#define ABSTRACTIMAGECLUSTERING_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include "util.h"

class AbstractImageClustering {
public:
    AbstractImageClustering(std::string imgAddr, int n);
    void inititalizeMeans();
private:
    cv::Mat img;
    int nClusters;
    int **means;
};

#endif // ABSTRACTIMAGECLUSTERING_H
