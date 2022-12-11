//
// Created by marshall on 14.12.2021.
//

#ifndef COUSERASPECYELLOW_MAXALGEBRA_H
#define COUSERASPECYELLOW_MAXALGEBRA_H
#include <Eigen/Dense>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
using namespace Eigen;
using namespace std;
template <typename T>
struct MaxAlg {
    T scalar;
    MaxAlg() = default;
    MaxAlg(T scalar) noexcept : scalar(scalar) {}
    explicit operator T() const noexcept {return scalar;}

    MaxAlg& operator+=(MaxAlg right) noexcept {
        scalar = std::max(scalar, right.scalar);
        return *this;
    }


    friend MaxAlg operator+(MaxAlg left, MaxAlg right) noexcept {
        left += right;
        return left;
    }
    MaxAlg& operator *=(MaxAlg right) noexcept {
        scalar *= right.scalar;
        return * this;
    }
    MaxAlg& operator /=(MaxAlg right) noexcept {
        scalar /= right.scalar;
        return * this;
    }
    friend MaxAlg operator-=(MaxAlg left, MaxAlg right) noexcept {
        return left;
    }
    friend MaxAlg operator*(MaxAlg left, MaxAlg right) noexcept {
        left *= right;
        return left;
    }
    friend MaxAlg operator-(MaxAlg left, MaxAlg right) noexcept {
        return left;
    }
    friend MaxAlg operator/(MaxAlg left, MaxAlg right) noexcept {
        left /= right;
        return left;
    }
    friend bool operator==(MaxAlg left, MaxAlg right) noexcept {
        return left.scalar == right.scalar;
    }
    friend bool operator!=(MaxAlg left, MaxAlg right) noexcept {
        return left.scalar != right.scalar;
    }
    friend bool operator>(MaxAlg left, MaxAlg right) noexcept {
        return left.scalar > right.scalar;
    }
    friend bool operator>=(MaxAlg left, MaxAlg right) noexcept {
        return left.scalar >= right.scalar;
    }
    friend bool operator<(MaxAlg left, MaxAlg right) noexcept {
        return left.scalar < right.scalar;
    }
    friend bool operator<=(MaxAlg left, MaxAlg right) noexcept {
        return left.scalar <= right.scalar;
    }
    friend std::ostream &operator<<(std::ostream & stream, MaxAlg right) noexcept {
        return stream << right.scalar;
    }

};
template<class T, Eigen::Index Rows, Eigen::Index Cols>
using MaxAlgMatrix = Eigen::Matrix<MaxAlg<T>,Rows,Cols>;

template<class T, Eigen::Index Rows,Eigen::Index Cols>
using MaxAlgArray = Eigen::Array<MaxAlg<T>, Rows,Cols>;

using MaxAlgMatrixXd = MaxAlgMatrix<double ,Eigen::Dynamic,Eigen::Dynamic>;
using MaxAlgVectorXd = MaxAlgMatrix<double, Eigen::Dynamic,1>;
using MaxAlgArrayXXd = MaxAlgArray<double , Eigen::Dynamic, Eigen::Dynamic>;
using MaxAlgArrayXd = MaxAlgArray<double, Eigen::Dynamic,1>;

double Tr(const MaxAlgMatrixXd& matrixXd) {
    double current_det = static_cast<double>(matrixXd.trace());
    MaxAlgMatrixXd temp = matrixXd;
    for (int i = 1; i < matrixXd.rows(); ++i){
        temp *= matrixXd;
//        std::cout << temp.cast<double>() << std::endl;
        if (current_det < static_cast<double>(temp.trace())) {
            current_det = static_cast<double>(temp.trace());
        }
    }

    return current_det;
}

std::ostream& operator<<(std::ostream & stream, const MaxAlgMatrixXd& matrixXd) {
    return stream << matrixXd.cast<double>();
}

template <typename T>
void PrintLog(const T& t, string hint = {},string delim = "\n") {
    std::cout << hint << delim;
    std::cout << t << std::endl;
}

MaxAlgMatrixXd Power(const MaxAlgMatrixXd& matrixXd, int n = 1 ,string hint = {}) {
    MaxAlgMatrixXd temp = matrixXd;
//    PrintLog("---------------","Вычисление cтепеней матрицы" + hint + ".");
//    PrintLog(temp,"Исходная матрица " + hint + " =");
    for (int i = 1; i < n; ++i) {
        temp *= matrixXd;
        PrintLog(temp,hint + "^" + to_string(i + 1) + " = ");
    }
    return temp;
}

MaxAlgMatrixXd Clini(const MaxAlgMatrixXd& matrixXd,string hint = {}){
   MaxAlgMatrixXd A(matrixXd.rows(),matrixXd.cols());
   MaxAlgMatrixXd temp = matrixXd;
//    PrintLog("---------------","Вычисление матрицы Клини " + hint + "*.");
//    PrintLog(temp,"Исходная матрица " + hint + " =");
   A.setIdentity();
    PrintLog(A,"I  = ");
    A += temp;

   for (int i = 1; i < matrixXd.rows() - 1; ++i) {
        temp *= matrixXd;
        A += temp;
        PrintLog(temp,hint + "^" + to_string(i+1) + " = ");

   }

    return A;


}
double SpectralRadius(const MaxAlgMatrixXd& matrixXd,string hint = {}) {
    int n = 1;
    double current_det = static_cast<double>(matrixXd.trace());
    MaxAlgMatrixXd temp = matrixXd;
//    PrintLog("---------------","Вычисление спектрального радиуса.");
//    PrintLog(temp,"Исходная матрица " + hint + " =");
    PrintLog(static_cast<double>(temp.trace()),"tr(" +hint + ") = "," ");
    for (int i = 1; i < matrixXd.rows(); ++i){
        temp *= matrixXd;
        ++n;
        // std::cout << temp.cast<double>() << std::endl;
        PrintLog(temp,hint + "^" + to_string(i + 1) + " = ");
        PrintLog(pow(static_cast<double>(temp.trace()), 1./n),
                 "tr^{1/" + std::to_string(n) + "} (" +hint + "^" + to_string(i + 1) + ") = "," ");
        if (current_det < pow(static_cast<double>(temp.trace()), 1./n)) {
            current_det = pow(static_cast<double>(temp.trace()), 1./n);
        }
/*        std::cout << temp.cast<double>() << std::endl;
        std::cout << current_det << std::endl;*/
    }

//    PrintLog(current_det,"Cпектральный радиус матрицы " + hint + " = "," ");
    return current_det;
}

inline double d(double p, double q) {
    // Assert(q != 0, "Division by zero");
    return p / q;
}

#if 0

MatrixXd MultiplyMaxAlgMat(const MaxAlgMatrixXd& a,const MaxAlgMatrixXd& b){
    MaxAlgMatrixXd c(a.rows(),b.cols());
    for (uint i = 0; i < a.rows(); ++i) {
        for (uint j = 0; j < b.cols(); ++j) {
            std::vector<double> values;
            for (uint k = 0; k < a.cols(); ++k) {
                values.push_back((a(i, k) * b(k, j)).scalar);
            }

            c(i,j) = *std::max_element(begin(values),end(values));
        }
    }

    return c.cast<double>();

}
MatrixXd AddMaxAlgMat(const MaxAlgMatrixXd& a,const MaxAlgMatrixXd& b) {
    MaxAlgMatrixXd c(a.rows(),a.cols());
    for (uint i = 0; i < a.rows(); ++i) {
        for (uint j = 0; j < a.cols(); ++j) {
            c(i,j) = std::max(a(i,j),b(i,j));
        }
    }

    return c.cast<double>();
}
MatrixXd GetSumMatrix(const MaxAlgMatrixXd & x,const MaxAlgMatrixXd & y) {
    MaxAlgMatrixXd r(2,2);

    r(0,0)  = max(x(0,0),y(0,0));
    r(0,1) =  max(x(0,1),y(0,1));
    r(1,0) = max(x(1,0),y(1,0));
    r(1,1) =  max(x(1,1),y(1,1));


    return  r.cast<double>();
}
MatrixXd GetMultipliedMatrix(const MaxAlgMatrixXd & x,const MaxAlgMatrixXd & y) {
    MaxAlgMatrixXd r(2,2);
    r(0,0)  = max(x(0,0)*y(0,0),x(0,1)*y(1,0));
    r(0,1) = max(x(0,0)*y(0,1),x(0,1)*y(1,1));
    r(1,0) = max(x(1,0)*y(0,0),x(1,1)*y(1,0));
    r(1,1) = max(x(1,0)*y(0,1),x(1,1)*y(1,1));
    return  r.cast<double>();
}


void TestMatrixAddition(){
    MaxAlgMatrixXd x(2,2);
    MaxAlgMatrixXd y(2,2);
    mt19937 gen;
    uniform_real_distribution<> unif(-10,10);
    uint test_count = 100;
    for (auto i = 0; i < test_count; ++i)
    {

        x << unif(gen) , unif(gen),
                unif(gen) , unif(gen);
        y << unif(gen), unif(gen),
                unif(gen),unif(gen);

        AssertEqual((x + y).cast<double>(),GetSumMatrix(x,y), "TestMatrixAddition " +  std::to_string(i + i));
    }


}

void TestCliniMatrix(){
    MaxAlgMatrixXd A(4,4),A_clini(4,4), B(4,4),B_clini(4,4);
    A << d(1,2) ,1,2, d(1,2),
            d(1,4),d(1,2),d(1,4),d(1,6),
            d(1,8),1,d(1,2),1,
            d(1,2), d(3,2), d(1,4),d(1,2);

    A_clini << 1,3,2,2,
            d(1,4),1,d(1,2),d(1,2),
            d(1,2),d(3,2),1,1,
            d(1,2),d(3,2),1,1;


    B << d(1,2),1,d(1,4),d(1,4),
            d(1,4),d(1,2),1,d(1,4),
            1,d(1,4),d(1,2),d(1,4),
            1,1,1,d(1,2);

    B_clini << 1,1,1,d(1,4),
            1,1,1,d(1,4),
            1,1,1,d(1,4),
            1,1,1,1;

    AssertEqual(Clini(A).cast<double>(),A_clini.cast<double>(),"Matrix A");
    AssertEqual(Clini(B).cast<double>(), B_clini.cast<double>(), "Matrix B");
}

void TestSpectralRadius(){
    MaxAlgMatrixXd C_1(4,4),C_2(6,6);
    C_1 << 1,4,2,2,
            1./4,1, 1./3, 1./4,
            1./2,3,1,3,
            1./2,4,1./3,1;

    C_2 << 1,4,3,1,3,4,
            d(1,4),1,7,3,d(1,5),1,
            d(1,3),d(1,7),1,d(1,5),d(1,5),d(1,6),
            1,d(1,3),5,1,1,d(1,3),
            d(1,3),5,5,1,1,3,
            d(1,4),1,6,3,d(1,3),1;
    double C2_sr = 2.59;
    double eps = 0.01;
    Assert(abs(SpectralRadius(C_2)- C2_sr) < eps,"Test C2");

    {
        MaxAlgMatrixXd B(4,4);
        B << 1,4,2,2,
                3,1,d(3,2),d(3,2),
                3,3,1,3,
                d(9,4),4,d(9,4),1;
        double B_sr = 3.4641;
        double eps = 0.01;
        Assert(abs(SpectralRadius(B)- B_sr) < eps,"Test B");

    }

}


void TestMatrixMultiplication(){
    MaxAlgMatrixXd x(2,2);
    MaxAlgMatrixXd y(2,2);
    mt19937 gen;
    uniform_real_distribution<> unif(-10,10);
    uint test_count = 100;
    for (auto i = 0; i < test_count; ++i) {

        x << unif(gen), unif(gen),
                unif(gen), unif(gen);
        y << unif(gen), unif(gen),
                unif(gen), unif(gen);

        AssertEqual((x * y).cast<double>(), GetMultipliedMatrix(x, y), "TestMatrixMultiplication " + std::to_string(i + i) );
    }


}
#endif

#endif //COUSERASPECYELLOW_MAXALGEBRA_H
