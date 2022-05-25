#include "em.h"

EM::EM(std::string imgAddr, int n) : AbstractClustering(imgAddr, n) {
    img = cv::imread(imgAddr);
    inititalizeMeans();
}

void EM::cluster() {
    while (!converged()) {
        EStep();
        MStep();
    }
}

bool EM::converged() {
    return false;
}

void EM::EStep() {

}

void EM::MStep() {

}

cv::Mat EM::reconstructImage() {
    int nearestMeanIndex;
    int sample[3];
    cv::Mat reconstructedImage(img.rows, img.cols, CV_8UC3);
    for (int i = 0; i < reconstructedImage.rows; i++) {
        for(int j = 0; j < reconstructedImage.cols; j++) {
            // std::cout <<  << " " << img.at<cv::Vec3b>(i,j)[1] << " " << img.at<cv::Vec3b>(i,j)[2] << std::endl;
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
