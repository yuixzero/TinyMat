//
// Created by Null on 2022/7/17.
//
#include "Mat.hpp"
#include <immintrin.h>

Mat::Mat(size_t row_, size_t col_) {
    row = row_;
    col = col_;
    // data = static_cast<float*> (aligned_alloc(256, sizeof(float)*row*col));
    data = new float[row*col];
    for (int i = 0; i < row*col; ++i) {
        data[i] = 0.0f;
    }
}


inline float Mat::operator()(size_t rowIndex, size_t colIndex) const {
    return data[rowIndex * col + colIndex];
}

void Mat::print() const {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout <<(*this)(i,j)<<" ";
        }
        std::cout << std::endl;
    }
}

inline size_t Mat::getRow() const {
    return this->row;
}

inline size_t Mat::getCol() const {
    return this->col;
}

Mat Mat::dot_n3(const Mat& m1,const Mat& m2) {
    size_t row_ = m1.getRow();
    size_t col_ = m2.getCol();

    Mat res(row_, col_);

    for (size_t i = 0; i < row_; ++i) {
        for (size_t j = 0; j <col_ ; ++j) {
            for (size_t k = 0; k < m1.getCol(); ++k) {
                res.data[i * col_ + j] += m1(i, k) * m2(k, j);
            }
        }
    }
    return res;
}

Mat Mat::dot_change_order(const Mat &m1, const Mat &m2) {
    size_t row = m1.getRow();
    size_t col = m2.getCol();

    Mat res(row ,col);

    for (size_t i = 0; i < row; ++i) {
        for (size_t k = 0; k < m1.getCol(); ++k) {
            float t = m1(i,k);
            for (size_t j = 0; j <col ; ++j) {
                res.data[i * col + j] += t * m2(k ,j);
            }
        }
    }
    return res;
}

Mat Mat::dot_parallel(const Mat& m1, const Mat& m2){
    size_t row = m1.getRow();
    size_t col = m2.getCol();

    Mat res(row ,col);
    size_t split = static_cast<size_t>(row / 2);
    std::thread t1(help_func, &m1, &m2, &res, 0, split);
    std::thread t2(help_func, &m1, &m2, &res, split, row);
    t1.join();
    t2.join();

    return res;

}
void Mat::help_func(const Mat* m1, const Mat* m2, Mat* res, size_t startIndex, size_t endIndex){

    for (size_t i = startIndex; i < endIndex; ++i) {
        for (size_t k = 0; k < m1->getCol(); ++k) {
            float t = (*m1)(i,k);
            for (size_t j = 0; j <m2->getCol() ; ++j) {
                res->data[i * m2->getCol() + j] += t * (*m2)(k ,j);
            }
        }
    }  
}

float Mat::_mm_vec_dot(const float *v1, const float *v2, const size_t len)
{
    float s[8] = {0};
    __m256 a,b;
    __m256 c = _mm256_setzero_ps();
    for (size_t i = 0; i < len; i+=8)
    {
        a = _mm256_load_ps(v1 + i);
        b = _mm256_load_ps(v2 + i);
        c =  _mm256_add_ps(c, _mm256_mul_ps(a, b));
    }
    _mm256_store_ps(s, c);
    auto sum = s[0] + s[1] + s[2] + s[3] + s[4] + s[5] + s[6] + s[7];
    for (size_t i = len - 1; i >= len - len % 8; i--) sum += v1[i] * v2[i];

    return sum;

}

Mat Mat::dot_avx2(const Mat& m1, const Mat& m2){
    size_t row = m1.getRow();
    size_t col = m2.getCol();

    Mat res(row ,col);

    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col ; ++j) {
            auto v1 = static_cast<float *>(aligned_alloc(256, sizeof(float) * m1.getCol()));
            auto v2 = static_cast<float *>(aligned_alloc(256, sizeof(float) * m2.getRow()));
            // memcpy(v1, m1.data + m1.getCol()*i, m1.getCol() * sizeof(float));
            for (size_t k = 0; k < m1.getCol(); ++k) v2[k] = m1.data[i * col + k];
            for (size_t k = 0; k < m2.getRow(); ++k) v2[k] = m2.data[k * col + j];
            res.data[i * col + j] = _mm_vec_dot(v1, v2, m2.getRow());
            delete[] v2;
        }
    }

    return res;
}


Mat Mat::dot_thread_pool(const Mat& m1, const Mat& m2){
    size_t row = m1.getRow();
    size_t col = m2.getCol();

    Mat res(row ,col);

    ThreadPool pool(2);
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col ; ++j) {
            pool.enqueue(calc_res, &m1, &m2, &res, i, j);
        }
    }

    return res;

}

void Mat::calc_res(const Mat* m1, const Mat* m2, Mat* res, size_t i, size_t j)
{
    for (size_t k = 0; k < m1->getCol(); k++)
    {
        res->data[i * m2->getCol() + j] += (*m1)(i, k) * (*m2)(k, j);
    }
    
}

Mat::Mat(MatrixXf& mat) {
    row = mat.rows();
    col = mat.cols();
    data = new float [row*col];

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            data[i * col + j] = mat(i,j);
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

    // data = static_cast<float*> (aligned_alloc(256, row*col*sizeof(float)));
    data = new float[row*col];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            data[i * col + j] = mat(i,j);
        }
    }
}



