// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>
#include "iostream"
#include "EdgeDetector.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector() {


}

// Destructor
EdgeDetector::~EdgeDetector() {

}


double** EdgeDetector::sobelGx = new double*[3]{
    new double[3]{-1.0,0.0,1.0},
    new double[3]{-2.0,0.0,2.0},
    new double[3]{-1.0,0.0,1.0}
};

double** EdgeDetector::sobelGy = new double*[3]{
        new double[3]{-1.0,-2.0,-1.0},
        new double[3]{0.0,0.0,0.0},
        new double[3]{1.0,2.0,1.0}
};

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {

    Convolution convolution = Convolution(sobelGx,3,3,1, true);

    ImageMatrix edgeX = convolution.convolve(input_image);


    convolution.setKernel(sobelGy,3,3);
    ImageMatrix edgeY = convolution.convolve(input_image);


    ImageMatrix gradientMatrix = ImageMatrix(edgeX.get_height(), edgeX.get_width());
    double sumGradients=0.0;

    for (int x = 0; x < edgeX.get_height() ; x++) {
        for (int y = 0; y < edgeX.get_width(); y++) {
            double gradient_value = sqrt(pow(edgeX.get_data(x, y), 2) + pow(edgeY.get_data(x, y), 2));
            sumGradients += gradient_value;
            gradientMatrix.setData(x, y, (double) gradient_value);
        }
    }

    double threshold = sumGradients / (edgeX.get_height() * edgeX.get_width());

    std::vector<std::pair<int,int>> edgeCoordinates;

    gradientMatrix.setMatrix([threshold, &edgeCoordinates](double &value, double y, double x) {
        if (value > threshold) {
            edgeCoordinates.emplace_back(y, x);
        }
    });

    return edgeCoordinates;

}

