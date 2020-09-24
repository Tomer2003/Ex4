extern "C" {
#include "Matrix.h"
}
#include "ClassMatrix.hpp"
#include "MatrixExceptions.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>

namespace matrix{
    Matrix::Matrix(const uint32_t height, const uint32_t width) :m_width(width), m_height(height){
        Exceptions::throwAppopriateErrorIfHas(matrix_create(&this->m_pMatrix, m_height, m_width));
    }

    Matrix::Matrix(const Matrix& matrix) :m_width(matrix.m_width), m_height(matrix.m_height){
        Exceptions::throwAppopriateErrorIfHas(matrix_copy(&this->m_pMatrix, matrix.m_pMatrix));
    }
    
    bool Matrix::checkIfHasValue(const int value) const{
        for(unsigned int row = 0; row < m_height; ++row){
            for(unsigned int column = 0; column < m_width; ++column){
                if(this->operator()(row, column) == value){
                    return true;
                }
            }
        }
        return false;
    }

    Matrix::Matrix(Matrix&& matrix) :m_width(matrix.m_width), m_height(matrix.m_height){
        this->m_pMatrix = matrix.m_pMatrix;
        matrix.m_pMatrix = nullptr;
    }

    Matrix& Matrix::operator=(const Matrix& other){
        if(this != &other){
            matrix_destroy(this->m_pMatrix);
            *this = Matrix(other);
        }
        return *this;
    }

    Matrix& Matrix::operator=(Matrix&& other){
         if(this != &other){
            matrix_destroy(this->m_pMatrix);  
            this->m_pMatrix = other.m_pMatrix;
            this->m_height = other.m_height;
            this->m_width = other.m_width;
            other.m_pMatrix = nullptr;
        }
        return *this;
    }

    void Matrix::matrixSetValue(const uint32_t rowIndex, const uint32_t colIndex, const double value){
        Exceptions::throwAppopriateErrorIfHas(matrix_setValue(this->m_pMatrix, rowIndex, colIndex, value));
    }
    
    uint32_t Matrix::matrixGetHeight() const{
        uint32_t result;
        Exceptions::throwAppopriateErrorIfHas(matrix_getHeight(this->m_pMatrix, &result));
        return result;
    } 

    uint32_t Matrix::matrixGetWidth() const{
        uint32_t result;
        Exceptions::throwAppopriateErrorIfHas(matrix_getWidth(this->m_pMatrix, &result));
        return result;
    }
    
    double Matrix::operator()(const uint32_t rowIndex, const uint32_t colIndex) const{
        double value = 0;
        Exceptions::throwAppopriateErrorIfHas(matrix_getValue(this->m_pMatrix, rowIndex, colIndex, &value));
        return value;
    }

    Matrix Matrix::operator+(const Matrix& matrix) const{
        Matrix result(matrix.m_height, matrix.m_width);
        if(matrix.m_height == 0 || matrix.m_width == 0){
            throw Exceptions::ErrorMatrixSizeNotAppopriate();
        }
        Exceptions::throwAppopriateErrorIfHas(matrix_add(&result.m_pMatrix, this->m_pMatrix, matrix.m_pMatrix));
        return result;
    }

    Matrix Matrix::operator*(const Matrix& matrix) const{
        Matrix result(matrix.m_height, this->m_height);
        if(matrix.m_height == 0 || this->m_height == 0){
            throw Exceptions::ErrorMatrixSizeNotAppopriate();
        }
        Exceptions::throwAppopriateErrorIfHas(matrix_multiplyMatrices(&result.m_pMatrix, this->m_pMatrix, matrix.m_pMatrix));
        return result; 
    }

    Matrix Matrix::operator*(const double scalar) const{
        Matrix result(*this);
        Exceptions::throwAppopriateErrorIfHas(matrix_multiplyWithScalar(result.m_pMatrix, scalar));
        return result;
    }

    Matrix Matrix::getMatrixFromFile(std::string fileName){
        std::ifstream inFile(fileName, std::ios::in);
        if(!inFile.is_open()){
            std::cerr << "Error: Fail to open file for reading!" << std::endl;
            exit(1);
        }
        auto content = std::string{std::istreambuf_iterator<char>{inFile},
                                std::istreambuf_iterator<char>{}};

        return getMatrixFromString(content);
    }

    Matrix Matrix::getMatrixFromString(std::string matrixString){
        matrixString.erase(std::remove(matrixString.begin(), matrixString.end(), ' '), matrixString.end());
        matrixString.erase(std::remove(matrixString.begin(), matrixString.end(), '\t'), matrixString.end());
        matrixString.erase(std::remove(matrixString.begin(), matrixString.end(), '\r'), matrixString.end());
        auto matrixWidth = std::count(matrixString.begin(), matrixString.begin() + matrixString.find("\n"), ',') + 1;
        std::replace(matrixString.begin(), matrixString.end(), '\n', ',');
        std::replace(matrixString.begin(), matrixString.end(), ',', ' ');
        std::vector<double> valuesArr;
        std::stringstream stringStreamContent(matrixString);
        double temp;
        while (stringStreamContent >> temp){
            valuesArr.push_back(temp);
        }

        auto matrixHeight = valuesArr.size() / matrixWidth;
        matrix::Matrix matrix(matrixHeight, matrixWidth);
        for(unsigned int row = 0; row < matrixHeight; ++row){
            for(unsigned int col = 0; col < matrixWidth; ++col){
                matrix.matrixSetValue(row, col, valuesArr[row * matrixWidth + col]);
            }
        }
        
        return matrix;
    }

    void Matrix::printMatrix() const{
        for(unsigned int row = 0; row < m_height; ++row){
            for(unsigned int column = 0; column < m_width; ++column){
                std::cout << this->operator()(row, column) << " ";
            }
            std::cout << std::endl;
        }
    }

    const std::string Matrix::getStringOfMatrix() const{
        std::string matrixStr = "";
         for(unsigned int row = 0; row < m_height; ++row){
            for(unsigned int column = 0; column < m_width; ++column){
                matrixStr += std::to_string((int)(this->operator()(row, column)));
                if(column != m_width - 1){
                    matrixStr += ",";
                }
            }
            matrixStr += '\n';
        }
        return matrixStr;
    }

    Matrix::~Matrix(){
        matrix_destroy(this->m_pMatrix);
    }
        
    Matrix operator*(double scalar, Matrix& matrix){
        return matrix * scalar;
    }  
}