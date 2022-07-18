#include "Mat.hpp"

using namespace Eigen;
using namespace std;

int main() {
    MatrixXf a1 = MatrixXf::Random(5, 3);
    Mat b1(a1);

    MatrixXf a2 = MatrixXf::Random(3, 5);
    Mat b2(a2);



    Mat c = Mat::dot_n3(b1, b2);
    c.print();
    cout << a1*a2 << endl;


}
