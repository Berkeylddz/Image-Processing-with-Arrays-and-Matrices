#include "ImageProcessor.h"
#include <iostream>

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    DecodeMessage decodeMessage;
    EdgeDetector edgeDetector;
    ImageSharpening imageSharpening;

    ImageMatrix sharpen_image = imageSharpening.sharpen(img,2);
    std::vector<std::pair<int,int>> edgePixels = edgeDetector.detectEdges(sharpen_image);
    std::string message = decodeMessage.decodeFromImage(sharpen_image,edgePixels);
    return message;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    EncodeMessage encodeMessage;
    EdgeDetector edgeDetector;
    ImageSharpening imageSharpening;

    ImageMatrix sharpen_image = imageSharpening.sharpen(img,2);

    std::vector<std::pair<int,int>> edgePixels = edgeDetector.detectEdges(img);

    return encodeMessage.encodeMessageToImage(img,message,edgePixels);
}
