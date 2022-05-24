#include "em.h"

EM::EM(std::string imgAddr, int n) : nClusters(n) {
    img = cv::imread(imgAddr);
    inititalizeMeans();
}

void EM::cluster() {

}

void EM::inititalizeMeans() {
    srand((unsigned)time(NULL));
    means = new int* [nClusters];
    for (int i = 0; i < nClusters; i++) {
        means[i] = new int [3];
        for (int j = 0; j < 3; j++) {
            means[i][j] = rand() % 256;
        }
    }
}
