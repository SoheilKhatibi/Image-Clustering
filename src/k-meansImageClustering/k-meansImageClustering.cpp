#include "k-meansImageClustering.h"

KMeansImageClustering::KMeansImageClustering(std::string imgAddr, int n) : AbstractImageClustering(imgAddr, n) {
    initializeBValues();
}

void KMeansImageClustering::cluster() {
    // int i = 0;
    while (!converged()) {
        BStep();
        MStep();
        // inititalizeMeans();
        // std::cout << "Iterate number " << i << std::endl;
        // printMeans();
        // cv::Mat reconstructedImage = reconstructImage();
        // displayImage(reconstructedImage);
        // i++;
    }
}

bool KMeansImageClustering::converged() {
    return false;
}

void KMeansImageClustering::BStep() {
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            for (int k = 0; k < nClusters; k++) {
                b[i][j][k] = 0;
            }
        }
    }

    int minIndex;
    int tmp[3];
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            tmp[0] = img.at<cv::Vec3b>(i, j)[0];
            tmp[1] = img.at<cv::Vec3b>(i, j)[1];
            tmp[2] = img.at<cv::Vec3b>(i, j)[2];

            minIndex = minimumDistanceIndex(tmp, means, nClusters);
            b[i][j][minIndex] = 1;
        }
    }
}

void KMeansImageClustering::MStep() {
    long int bSum, XBSumBlue, XBSumGreen, XBSumRed;
    for (int k = 0; k < nClusters; k++) {
        bSum = 0;
        XBSumBlue = 0;
        XBSumGreen = 0;
        XBSumRed = 0;
        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                bSum += b[i][j][k];
                XBSumBlue += b[i][j][k] * img.at<cv::Vec3b>(i, j)[0];
                XBSumGreen += b[i][j][k] * img.at<cv::Vec3b>(i, j)[1];
                XBSumRed += b[i][j][k] * img.at<cv::Vec3b>(i, j)[2];
            }
        }
        if (bSum != 0) { // Prevent floating point segmentation fault when no samples are labeled by the current mean
            means[k][0] = XBSumBlue / bSum;
            means[k][1] = XBSumGreen / bSum;
            means[k][2] = XBSumRed / bSum;
        }
    }
}

void KMeansImageClustering::initializeBValues() {
    b = new int** [img.rows];
    for (int i = 0; i < img.rows; i++) {
        b[i] = new int* [img.cols];
        for (int j = 0; j < img.cols; j++) {
            b[i][j] = new int [nClusters];
        }
    }
    BStep();
}
