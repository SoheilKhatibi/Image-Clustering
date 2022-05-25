#include "abstractImageClustering.h"

AbstractImageClustering::AbstractImageClustering(std::string imgAddr, int n) : nClusters(n) {
    img = cv::imread(imgAddr);
    inititalizeMeans();
}

void AbstractImageClustering::inititalizeMeans() {
    srand((unsigned)time(NULL));
    means = new int* [nClusters];
    for (int i = 0; i < nClusters; i++)
        means[i] = new int [3];

    for (int i = 0; i < nClusters; i++) {
        for (int j = 0; j < 3; j++) {
            means[i][j] = rand() % 256;
            // std::cout << means[i][j] << "\t";
        }
        // std::cout<<std::endl;
        // img = cv::Mat(200, 200, CV_8UC3, cv::Scalar(means[i][0], means[i][1], means[i][2]));
        // cv::imshow("img", img);
        // cv::waitKey(1);
    }
}
