#ifndef ABSTRACTCLUSTERING_H
#define ABSTRACTCLUSTERING_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

class AbstractClustering {
public:
    AbstractClustering(std::string imgAddr, int n);
    void inititalizeMeans();
private:
    cv::Mat img;
    int nClusters;
    int **means;
};

#endif // ABSTRACTCLUSTERING_H
