//
// Created by Null on 2022/7/17.
//
#include "Mat.hpp"


Mat::Mat(size_t row_, size_t col_) {
    row = row_;
    col = col_;
    data = new float [row*col];
    for (int i = 0; i < row*col; ++i) {
        data[i] = 0;
    }
}


inline float Mat::operator()(size_t rowIndex, size_t colIndex) const {
    return data[rowIndex * row + colIndex];
}

void Mat::print() const {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout <<(*this)(i,j)<<" ";
        }
        std::cout << std::endl;
    }
}

size_t Mat::getRow() const {
    return this->row;
}

size_t Mat::getCol() const {
    return this->col;
}

Mat Mat::dot_n3(Mat &m1, Mat &m2) {
    Mat res(m1.getCol(), m2.getRow());
    size_t index = 0;
    for (size_t i = 0; i < m1.getCol(); ++i) {
        for (size_t j = 0; j <m2.getRow() ; ++j) {
            for (int k = 0; k < m1.getRow(); ++k) {
                res.data[index] += m1(i, k) * m2(k, j);
            }
            index++;
        }
    }
    return res;
}

Mat::Mat(Matrix2d& mat) {
    row = mat.rows();
    col = mat.cols();
    data = new float [row*col];

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            data[i * row + j] = static_cast<float>(mat(i,j));
        }
    }
}

Mat::~Mat()
{
    delete[] data;
    data = nullptr;
}

Mat::Mat(Mat& mat)
{
    row = mat.row;
    col = mat.col;

    data = new float [row*col];
        for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            data[i * row + j] = mat(i,j);
        }
    }
}

