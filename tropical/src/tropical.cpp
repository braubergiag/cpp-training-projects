#include "../include/tropical.h"



using std::string;
std::ostream& operator<<(std::ostream & stream, const MaxAlgMatrixXd& matrixXd) {
    return stream << matrixXd.cast<double>();
}


double SpectralRadius(const MaxAlgMatrixXd& matrixXd,string hint) {
    int n = 1;
    double current_det = static_cast<double>(matrixXd.trace());
    MaxAlgMatrixXd temp = matrixXd;
//    PrintLog("---------------","Вычисление спектрального радиуса.");
//    PrintLog(temp,"Исходная матрица " + hint + " =");
    PrintLog(static_cast<double>(temp.trace()),"tr(" +hint + ") = "," ");
    for (int i = 1; i < matrixXd.rows(); ++i){
        temp *= matrixXd;
        ++n;
        PrintLog(temp,hint + "^" + to_string(i + 1) + " = ");
        PrintLog(pow(static_cast<double>(temp.trace()), 1./n),
                 "tr^{1/" + std::to_string(n) + "} (" +hint + "^" + to_string(i + 1) + ") = "," ");
        if (current_det < pow(static_cast<double>(temp.trace()), 1./n)) {
            current_det = pow(static_cast<double>(temp.trace()), 1./n);
        }
    }

//    PrintLog(current_det,"Cпектральный радиус матрицы " + hint + " = "," ");
    return current_det;
}

MaxAlgMatrixXd Clini(const MaxAlgMatrixXd& matrixXd,string hint){
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


MaxAlgMatrixXd power(const MaxAlgMatrixXd &matrixXd, int n) {
    MaxAlgMatrixXd temp = matrixXd;
    for (int i = 1; i < n; ++i) {
        temp *= matrixXd;
    }
    return temp;
}
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