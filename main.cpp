#include "Mat.hpp"

using namespace Eigen;
using namespace std;

int main() {
    MatrixXf a1 = MatrixXf::Random(560,560);
    Mat b1(a1);


    MatrixXf a2 = MatrixXf::Random(560,560);
    Mat b2(a2);

    clock_t s = clock();
    Mat c1 = Mat::dot_change_order(b1, b2);
    clock_t e = clock();
    cout <<"Time use: "<< (double)(e - s) / CLOCKS_PER_SEC << "s"<<endl;

    s = clock();
    MatrixXf c2 = a1 * a2;
    e = clock();
    cout <<"Time use: "<< (double)(e - s) / CLOCKS_PER_SEC << "s"<<endl;

    // cout<< c2 << endl;
    // cout << "-------------------------------------------------------" << endl;
    // c1.print();

}
