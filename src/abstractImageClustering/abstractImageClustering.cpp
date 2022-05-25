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

cv::Mat AbstractImageClustering::reconstructImage() {
    int nearestMeanIndex;
    int sample[3];
    cv::Mat reconstructedImage(img.rows, img.cols, CV_8UC3);
    for (int i = 0; i < reconstructedImage.rows; i++) {
        for(int j = 0; j < reconstructedImage.cols; j++) {
            sample[0] = img.at<cv::Vec3b>(i, j)[0];
            sample[1] = img.at<cv::Vec3b>(i, j)[1];
            sample[2] = img.at<cv::Vec3b>(i, j)[2];

            nearestMeanIndex = minimumDistanceIndex(sample, means, nClusters);

            reconstructedImage.at<cv::Vec3b>(i, j)[0] = means[nearestMeanIndex][0];
            reconstructedImage.at<cv::Vec3b>(i, j)[1] = means[nearestMeanIndex][1];
            reconstructedImage.at<cv::Vec3b>(i, j)[2] = means[nearestMeanIndex][2];
        }
    }

    return reconstructedImage;
}
