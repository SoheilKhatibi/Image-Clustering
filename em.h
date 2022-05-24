#ifndef EM_H
#define EM_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

class EM {
public:
    EM(std::string imgAddr, int n);
    void cluster();
    void inititalizeMeans();
private:
    cv::Mat img;
    int nClusters;
    int **means;
};

#endif