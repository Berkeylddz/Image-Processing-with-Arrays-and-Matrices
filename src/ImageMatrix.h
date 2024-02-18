#ifndef IMAGE_MATRIX_H
#define IMAGE_MATRIX_H

#include <string>
#include "functional"
#include "ImageLoader.h"

class ImageMatrix {
public:
    // Constructors and Destructor
    ImageMatrix(); // Default constructor
    ImageMatrix(const std::string &filepath); // Parameterized constructor for loading image from file
    ImageMatrix(int imgHeight, int imgWidth); // Constructor for creating a blank image of given size
    ImageMatrix(const double** d, int imgHeight, int imgWidth); // Parameterized constructor - direct initialization with 2D matrix
    ImageMatrix(const ImageMatrix &other); // Copy constructor
    ImageMatrix& operator=(const ImageMatrix &other); // Copy assignment operator
    ~ImageMatrix(); // Destructor

    // Overloaded operators
    ImageMatrix operator+(const ImageMatrix &other) const;
    ImageMatrix operator-(const ImageMatrix &other) const;
    ImageMatrix operator*(const double &scalar) const; // Scalar multiplication

    double** get_data() const; // Getter function to access the data in the matrix
    double get_data(int i, int j) const; // Getter function to access the data at the index (i, j)
    void setData(int i, int j, double value) const;
    void setData(double** new_data);


    int get_height() const;
    int get_width() const;

    void addPadding(int paddingSize, double paddingValue);
    void setMatrix(std::function<void(double&, int, int )> function)const;

    template<typename T>
    static T** create_matrix(int height, int width, T value){
        T** matrix = new T*[height];
        for(int a=0; a < height; ++a){
            matrix[a] = new T[width];
            for (int b = 0; b < width; ++b) {
                matrix[a][b] = value;
            }
        };
        return matrix;
    }

    template<typename T>
    static T** create_matrix(T** input_matrix, int height, int width, std::function<T(T)> map){
        T** matrix = new T*[height];
        for(int i=0; i<height;++i){
            matrix[i] = new T[width];
            for (int j = 0; j < width; ++j) {
                matrix[i][j] = map(input_matrix[i][j]);
            }
        }
        return matrix;
    }


private:
    // Private member variables to store the image data
    double** data; // 2D array to store image data
    int height; // Height of the matrix
    int width; // Width of the matrix



};

#endif // IMAGE_MATRIX_H
