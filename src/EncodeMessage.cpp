#include "EncodeMessage.h"
#include <cmath>
#include "iostream"
#include "bitset"

// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {

    std::string encodedMessage;

    for (int i = 0; i < message.size(); i++) {

        if(prime(i)){
            int decimalValue = static_cast<int>(message[i]);
            int value = decimalValue + get_fibonacci(i);

            if(value <= 32){
                value+=33;
            }
            else if(value >= 127){
                value=126;
            }

            char ascii_char = static_cast<char>(decimalValue);
            encodedMessage += ascii_char;
        }
        else{
            encodedMessage += message[i];
        }
    }


    int value = static_cast<int>(encodedMessage.length() / 2);
    int index;
    std::string reorderedMessage;

    for (int i = 0; i < encodedMessage.length() ; i++) {
        index = (value + i) % static_cast<int>(encodedMessage.length());
        reorderedMessage += encodedMessage[index];
    };


    ImageMatrix encodedImage = ImageMatrix(img);

    std::string messageee="";

    for (int i = 0; i < reorderedMessage.length(); i++) {

        int decimal_value = reorderedMessage[i];

        std::bitset<7> binaryValue(decimal_value);

        messageee = messageee+binaryValue.to_string();
    }


    int i=0;

    for (const auto& position : positions) {
        int firstValue = position.first;   // 'first' değeri
        int secondValue = position.second; // 'second' değeri


        std::bitset<7> binaryValuee(encodedImage.get_data(firstValue,secondValue));


        if(binaryValuee.test(0)){
            // En sağdaki bit 1 olarak ayarlı.
            char num = messageee[i];
            int Int = num - '0';

            if(Int == 0){
                double value = encodedImage.get_data(firstValue,secondValue)-1;
                encodedImage.setData(firstValue,secondValue,(double) value);

            }
            i++;

        }
        else {
            char num = messageee[i];
            int Int = num - '0';

            if(Int == 1){
                double value = encodedImage.get_data(firstValue,secondValue)+1;
                encodedImage.setData(firstValue,secondValue,(double) value);
            }

            i++;
        }

    }

    return encodedImage;
}




bool EncodeMessage::prime(int a) {
    if (a <= 1) {
        return false;
    }
    if (a <= 3) {
        return true;
    }
    if (a % 2 == 0 || a % 3 == 0) {
        return false;
    }

    for (int i = 5; i * i <= a; i += 6) {
        if (a % i == 0 || a % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}


int EncodeMessage::get_fibonacci(int i) {
    if (i <= 0) {
        return 0;
    } else if (i == 1) {
        return 1;
    } else {
        int prev = 0;
        int current = 1;
        int fib = 0;

        for (int n = 2; n <= i; n++) {
            fib = prev + current;
            prev = current;
            current = fib;
        }

        return fib;
    }
}

