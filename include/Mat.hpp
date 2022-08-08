//
// Created by Null on 2022/7/17.
//

#ifndef MAT_MAT_HPP
#define MAT_MAT_HPP

#include <string>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <thread>
#include "Thread.hpp"

// #include <cblas.h>

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
    static Mat dot_change_order(const Mat& m1, const Mat& m2);
    static Mat dot_parallel(const Mat& m1, const Mat& m2);
    static Mat dot_thread_pool(const Mat& m1, const Mat& m2);
    static Mat dot_avx2(const Mat& m1, const Mat& m2);
    static void help_func(const Mat* m1, const Mat* m2, Mat* res, size_t startIndex, size_t endIndex);
    static void calc_res(const Mat* m1, const Mat* m2, Mat* res, size_t i, size_t j);
    static float _mm_vec_dot(const float *v1, const float *v2, const size_t len);

};

#endif //MAT_MAT_HPP
