#include "Mat.hpp"

using namespace Eigen;
using namespace std;

int main() {
    Matrix2d a = Matrix2d::Random(4, 4);
    Mat b(a);
    cout << a << endl;
    b.print();

    Mat c = Mat::dot_n3(b, b);
    c.print();
    cout << a*a << endl;


}
