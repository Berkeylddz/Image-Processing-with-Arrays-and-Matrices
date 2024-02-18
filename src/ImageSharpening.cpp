#include "ImageSharpening.h"
#include "Convolution.h"
#include "ImageSharpening.h"
#include "iostream"
// Default constructor
ImageSharpening::ImageSharpening() {

}

ImageSharpening::~ImageSharpening(){

}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {

    Convolution convolution;

    ImageMatrix blurredImage = convolution.convolve(input_image);

    for (int i = 0; i < blurredImage.get_height(); i++) {
        for (int j = 0; j < blurredImage.get_width(); j++) {
            double value = blurredImage.get_data(i,j)/9.0;
            blurredImage.setData(i,j,(double)value);
        }
    }

    ImageMatrix sharpImage = input_image + ((input_image-blurredImage)*k);

    for (int i = 0; i < sharpImage.get_height(); ++i) {
        for (int j = 0; j < sharpImage.get_width(); ++j) {

            if(sharpImage.get_data(i,j)<0){
                sharpImage.setData(i,j,(double)0);
            }
            else if(sharpImage.get_data(i,j)>256){
                sharpImage.setData(i,j,(double)255);
            }
        }
    }


    return sharpImage;

}
