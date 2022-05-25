#include "emImageClustering.h"

EMImageClustering::EMImageClustering(std::string imgAddr, int n) : AbstractImageClustering(imgAddr, n) {
}

void EMImageClustering::cluster() {
    // int i = 0;
    while (!converged()) {
        EStep();
        MStep();
        // inititalizeMeans();
        // std::cout << "Iterate number " << i << std::endl;
        // cv::Mat reconstructedImage = reconstructImage();
        // displayImage(reconstructedImage);
        // i++;
    }
}

bool EMImageClustering::converged() {
    return false;
}

void EMImageClustering::EStep() {

}

void EMImageClustering::MStep() {

}
