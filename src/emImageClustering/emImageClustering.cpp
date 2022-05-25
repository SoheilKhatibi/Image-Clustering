#include "emImageClustering.h"

EMImageClustering::EMImageClustering(std::string imgAddr, int n) : AbstractImageClustering(imgAddr, n) {
}

void EMImageClustering::cluster() {
    while (!converged()) {
        EStep();
        MStep();
    }
}

bool EMImageClustering::converged() {
    return false;
}

void EMImageClustering::EStep() {

}

void EMImageClustering::MStep() {

}

cv::Mat EMImageClustering::reconstructImage() {
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
    displayImage(reconstructedImage);

    return reconstructedImage;
}
