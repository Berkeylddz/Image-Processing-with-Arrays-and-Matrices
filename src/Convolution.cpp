#include <iostream>

#include "Convolution.h"
#include <iomanip>
// Default constructor 
Convolution::Convolution() : height(3), width(3), stride(1), padding(true)  {


    kernel = new double*[height]{
        new double[width]{1,1,1},
        new double[width]{1,1,1},
        new double[width]{1,1,1}
    };

}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad): height(kh),width(kw),
    stride(stride_val),padding(pad),kernel(customKernel){

    kernel= ImageMatrix::create_matrix<double>(kernel, height, width, [](double value) {
        return value;
    });



}

// Destructor
Convolution::~Convolution() {
    if(kernel != nullptr){
        for (int a=0; a < height; a++){
            delete[] kernel[a];
        }
        delete[] kernel;
        kernel= nullptr;
    }
}


// Copy constructor
Convolution::Convolution(const Convolution &other): height(other.height),width(other.width),stride(other.stride),padding(other.padding){

    kernel= ImageMatrix::create_matrix<double>(other.kernel, height, width, [](double value) {
        return value;
    });
}



// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this != &other) {
        // Önce mevcut kaynakları temizle
        if (kernel != nullptr) {
            for (int a = 0; a < height; a++) {
                delete[] kernel[a];
            }
            delete[] kernel;
            kernel = nullptr;
        }

        // Diğer nesnenin verilerini kopyala
        height = other.height;
        width = other.width;
        stride = other.stride;
        padding = other.padding;

        kernel = ImageMatrix::create_matrix<double>(other.kernel, height, width, [](double value) {
            return value;
        });
    }
    return *this;
}






// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {


    int new_height = (input_image.get_height() - height + 2 * padding) / stride + 1;
    int new_width = (input_image.get_width() - width + 2 * padding) / stride + 1;


    ImageMatrix convolved_image(new_height, new_width);

    ImageMatrix padding_image(input_image);

    if(padding){
        (padding_image).addPadding(1, 0);
    }

    for (int a = 0; a <input_image.get_height() - 2*(!padding); a+=stride) {
        for (int b = 0; b < input_image.get_width() - 2*(!padding); b+=stride) {

            double sum=0;

            for (int c = 0; c < height; c++) {
                for (int d = 0; d < width; d++) {
                    sum += (padding_image).get_data(c + a, b + d) * kernel[c][d];
                }
            }
            convolved_image.setData(a / stride, b / stride, (double) sum);
        }
    }

    return convolved_image;




    /*for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            std::cout << convolved_image.get_data(i,j) << " ";
        }std::cout << "\n";

    }*/
    //    std::cout << "Merhaba, Dünya!" << std::endl;

}

void Convolution::setStride(int value) {
    stride=value;
}

void Convolution::setPadding(int value) {
    padding=value;
}

void Convolution::setKernel(double **new_kernel, int kh, int kw) {
    if(kernel != nullptr){
        for (int x=0; x < height; x++){
            delete[] kernel[x];
        }
        delete[] kernel;
        kernel= nullptr;
    }
    height=kh;
    width=kw;

    kernel= ImageMatrix::create_matrix<double>(new_kernel, height, width, [](double value) {
        return value;
    });
}
