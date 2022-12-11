#include <algorithm>
#include <iostream>

#include <Eigen/Dense>


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
MaxAlgMatrixXd Power(const MaxAlgMatrixXd& matrixXd, int n = 1 ,string hint = {}) {
    MaxAlgMatrixXd temp = matrixXd;
    PrintLog("---------------","Вычисление cтепеней матрицы" + hint + ".");
    PrintLog(temp,"Исходная матрица " + hint + " =");
    for (int i = 1; i < n; ++i) {
        temp *= matrixXd;
        PrintLog(temp,hint + "^" + to_string(i + 1) + " = ");
    }
    return temp;
}
MaxAlgMatrixXd Clini(const MaxAlgMatrixXd& matrixXd,string hint = {}){
    MaxAlgMatrixXd A(matrixXd.rows(),matrixXd.cols());
    MaxAlgMatrixXd temp = matrixXd;
    PrintLog("---------------","Вычисление матрицы Клини " + hint + "*.");
    PrintLog(temp,"Исходная матрица " + hint + " =");
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
    PrintLog("---------------","Вычисление спектрального радиуса.");
    PrintLog(temp,"Исходная матрица " + hint + " =");
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

    PrintLog(current_det,"Cпектральный радиус матрицы " + hint + " = "," ");
    return current_det;
}
