// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up

}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {

    std::string binary_result;
    std::string decoded_message;



    for (const auto& pixel : edgePixels) {
        int lsb = static_cast<int>(image.get_data(pixel.first, pixel.second)) & 1; // LSB'yi al

        binary_result += std::to_string(lsb); // LSB'yi ikili dizeye ekle
    }



    while (binary_result.length()%7!=0){
        binary_result = "0"+ binary_result;
    }

    for (size_t i = 0; i < binary_result.length(); i += 7) {

        std::string binarySegment = binary_result.substr(i, 7); // 7 bitlik bölümü al


        int asciiValue = std::stoi(binarySegment, nullptr, 2); // İkiliyi ondalığa dönüştür

        // ASCII değerini düzeltilmiş bir karaktere dönüştür
        if (asciiValue <= 32) {
            asciiValue += 33;
        } else if (asciiValue == 127) {
            asciiValue = 126;
        }

        char character = static_cast<char>(asciiValue);
        decoded_message += character; // Karakteri şifrelenmiş mesaja ekle
    }



    return decoded_message;


}

