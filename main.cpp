#include "Mat.hpp"

using namespace Eigen;
using namespace std;

int main() {
    Matrix2d a = Matrix2d::Random(2, 2);
    Mat b(a);
    cout << a << endl;
    b.print();
}
