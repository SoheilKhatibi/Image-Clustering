#include "util.h"
#include "k-meansImageClustering.h"
#include "emImageClustering.h"

int main(int argc, char** argv) {

    // for (int i = 0; i < argc; i++) {
    //     std::cout << argv[i] << std::endl;
    // }

    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <imageAddress> <nClusters>" << std::endl;
        return 1;
    }

    // KMeansImageClustering algorithm(argv[1], atoi(argv[2]));
    EMImageClustering algorithm(argv[1], atoi(argv[2]));
    algorithm.cluster();

    // arma::Cube<int> a(5, 4, 3, arma::fill::ones);
    // a.print("Cube:");
    // a(4, 3, 2) = 0;
    // a.slice(2).col(3).row(4).print("Matrix:");

    // cv::Mat img;
    // loadImage(img, "Lenna.png");
    // // displayImage(img);
    // arma::Mat<int> armaImage = opencv2arma(img);
    // cv::Mat opencvImage = arma2opencv(armaImage);
    // displayImage(opencvImage);

    return 0;
}
