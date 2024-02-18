#include "ImageMatrix.h"
#include <iostream>


// Default constructor
ImageMatrix::ImageMatrix(): height(0),width(0),data(nullptr){

}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    data = ImageMatrix::create_matrix(height, width, (double) 0);

}

// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Allocate memory for the matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }


}



// Destructor
ImageMatrix::~ImageMatrix() {
    if(data != nullptr){
        for (int i=0;i<height;i++) {
            delete[] data[i];
        }
        delete[] data;
        data= nullptr;
    }
}

// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth):height(imgHeight),width(imgWidth){

    data = ImageMatrix::create_matrix<double>(const_cast<double **>(inputMatrix), height, width,
                                              [](double d) -> double {
                                                  return d;
                                              });

}


// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other):height(other.height), width(other.width) {
    data = ImageMatrix::create_matrix<double>(other.get_data(), height, width, [](double a) -> double {
        return a;
    });
}



// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
    ImageMatrix new_matrix(other);
    return new_matrix;
}



// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
    ImageMatrix matrix(height,width);

    for(int y=0; y<matrix.height;y++){
        for(int x=0; x<matrix.width;x++){
            matrix.setData(y,x, get_data(y,x) + other.get_data(y,x));
        }
    }
    return matrix;

}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    ImageMatrix matrix(height,width);

    for(int y=0; y<matrix.height;y++){
        for(int x=0; x<matrix.width;x++){
            matrix.setData(y,x, get_data(y,x) - other.get_data(y,x));
        }
    }
    return matrix;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {

    //datayla scalar ı çarpıcaz
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i][j] = get_data(i,j)*scalar;
        }
    }
    return reinterpret_cast<const ImageMatrix &>(data);

}

int ImageMatrix::get_height() const{
    return height;
}

int ImageMatrix::get_width() const{
    return width;
}

// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return this->data;
}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    return this->data[i][j];
}


void ImageMatrix::setData(int i, int j, double value) const{
    this->data[i][j] = value;
}

void ImageMatrix::setData(double **new_data) {
    if(data != nullptr){
        for (int i = 0; i < height; i++) {
            delete data[i];
        }
        delete data;
    }
    data = new_data;
}



void ImageMatrix::addPadding(int paddingSize, double paddingValue) {
    int newHeight = height + 2 * paddingSize;
    int newWidth = width + 2 * paddingSize;

    double** newData = ImageMatrix::create_matrix(newHeight, newWidth, paddingValue);

    for (int i = 0; i < height ; i++) {
        for (int j = 0; j < width; j++) {
            newData[i + paddingSize][j + paddingSize] = this->get_data(i, j);
        }
    }

    this->setData(newData);
    height=newHeight;
    width=newWidth;

}

void ImageMatrix::setMatrix(std::function<void(double&, int, int)> function) const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            function(data[y][x], y, x);
        }
    }
}

