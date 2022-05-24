#include "k-means.h"

KMeans::KMeans(std::string imgAddr, int n) : AbstractClustering(imgAddr, n) {
    img = cv::imread(imgAddr);
    inititalizeMeans();
}

void KMeans::cluster() {

}
