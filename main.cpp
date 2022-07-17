//#include <eigen3/Eigen/Dense>
#include "Mat.hpp"

//using namespace Eigen;
using namespace std;

int main() {
//    Matrix2d a;
//    a<<1,2,3,4;
//
//    Matrix2d b;
//    b<<1,2,3,4;
//
//    cout << a*b;

    Mat c(2, 2);
    Mat d(2, 2);

    for (int i = 1; i <= 4; ++i) {
        c.data[i-1] = static_cast<float>(i);
        d.data[i-1] = static_cast<float>(i);
    }
//    c.print();

    Mat res = Mat::dot_n3(c ,d);
    res.print();

}
