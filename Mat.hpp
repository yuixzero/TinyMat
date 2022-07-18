//
// Created by Null on 2022/7/17.
//

#ifndef MAT_MAT_HPP
#define MAT_MAT_HPP

#include <string>
#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

class Mat
{
public:
    size_t row{};
    size_t col{};
    float* data{};

public:
    Mat(size_t row, size_t col);
    explicit Mat(MatrixXf & mat);
    Mat(Mat& mat);
    ~Mat();
    float operator() (size_t rowIndex, size_t colIndex) const;
    [[nodiscard]] size_t getRow() const;
    [[nodiscard]] size_t getCol() const;
    void print() const;

    static Mat dot_n3(const Mat& m1, const Mat& m2);
    static Mat dot_change_order(Mat& m1, Mat& m2);

};

#endif //MAT_MAT_HPP
