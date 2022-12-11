
#include <iostream>

#include <Eigen/Dense>
#include <vector>
#include "../include/max_algebra.h"
#include "../include/tropical.h"

using namespace Eigen;
using namespace std;

// 1.1. Построение генерирующей матрицы оптимальных весов
MaxAlgMatrixXd construction_generating_matrix_optimal_weights(const MaxAlgMatrixXd & Criteria,double lambda){
    MaxAlgMatrixXd D = Clini(d(1, lambda) * Criteria,"(1/lambda * C)");
    return D;
}


/* 1.2 Вычисление по матрице D со столбцами d_1 , . . . , d_K
* наилучшего дифференцирующего вектора весов
*/

int get_best_differentiating_vector(const MaxAlgMatrixXd & D){

    MaxAlgVectorXd I(D.rows());
    I.setOnes();
    double current_max = 0;
    int l_ = 0;
    for (auto i = 0; i < D.cols(); ++i) {
        MaxAlgMatrixXd x = D.col(i);
        MaxAlgMatrixXd x_ = D.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            l_ =  i;
            current_max = r1(0).scalar;
        }

    }
    return l_;

}

void MinMaxLogApprox(const std::vector<MaxAlgMatrixXd> & Alternatives, const MaxAlgMatrixXd & Criteria, const string & hint){


    std::cout << hint << std::endl;

    std::cout << Criteria << std::endl;

    double lambda = SpectralRadius(Criteria, "C");
    MaxAlgMatrixXd D = construction_generating_matrix_optimal_weights(Criteria,lambda);
    std::cout << "D = \n" << D << std::endl;

    int l_ = get_best_differentiating_vector(D);

    std::cout << " Index l = " <<      l_ << std::endl;
    MaxAlgMatrixXd v = D.col(l_) * d(1,static_cast<double>(D.col(l_).sum()));
    std::cout << "v = \n" << v << std::endl;
/* 1.3
 * Вычисление по матрице D наихудшего дифференцирующего вектора весов
 * */
//    std::cout << "1.3." <<
//              " Вычисление по матрице D наихудшего дифференцирующего вектора весов\n";

    MaxAlgVectorXd I(D.rows());
    I.setOnes();

    MaxAlgMatrixXd w = (I.transpose() * D).array().inverse();
    std::cout << "w = " << w.cast<double>() << std::endl;
    /* 2
     * Определение для заданных матриц A_1 , . . . , A_K парных сравнений
    N альтернатив и вектора весов v = (v_1 , . . . , v_K )^T наилучшего диф-
    ференцирующего вектора рейтингов альтернатив.
     * */
//    std::cout << "2\n"
//                 " Определение для заданных матриц A_1 , . . . , A_K парных сравнений\n" <<
//              " N альтернатив и вектора весов v = (v_1 , . . . , v_K )^T наилучшего диф-\n" <<
//              " ференцирующего вектора рейтингов альтернатив.\n";

    /* 2.1
     * Вычисление взвешенной суммы матриц парных сравнений
     * */
    std::cout << "2.1";
    vector<MaxAlgMatrixXd> mat_ = Alternatives;
    for (auto i = 0; i < v.size(); ++i){
        mat_[i] *= v(i);
    }
    MaxAlgMatrixXd P(mat_.at(0).rows(),mat_.at(0).cols());
    P.setIdentity();
    for (auto const & mat : mat_){
        P += mat;
    }
    std::cout << "Matrix P = \n" << P << std::endl;

    /* 2.2
     * Построение генерирующей матрицы оптимальных рейтингов альтернатив
     * */

    std::cout << "2.2.\n";
    double mu = SpectralRadius(P,"P");
    std::cout << "Spectral Radius P = " << mu << std::endl;
    MaxAlgMatrixXd Q = Clini(d(1,mu) * P,"(mu^-1 P)");
    std::cout << " Matrix Clini Q = (mu^-1 P)* = \n";
    std::cout << Q << std::endl;
    /* 2.3
     * Вычисление по матрице Q со столбцами q 1 , . . . , q N наилучшего
     * дифференцирующего вектора рейтингов альтернатив
     * */

    std::cout << " 2.3\n";
    I.resize(Q.rows());
    I.setOnes();
    double current_max = 0;
    int m_ = 0;
    for (auto i = 0; i < Q.cols(); ++i) {
        MaxAlgMatrixXd x = Q.col(i);
        MaxAlgMatrixXd x_ = Q.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            m_ =  i;
            current_max = r1(0).scalar;
        }

    }
    std::cout << " Index m = " << m_ << std::endl;
    MaxAlgMatrixXd X = Q.col(m_) * d(1,static_cast<double>(Q.col(l_).sum()));
//    Vector3d X_test_1 = {1,d(2*lmb,mu),d(mu,9)};
//    Vector4d X_test_2 = {d(mu,6),d(mu,4),1,d(1,2)};
    std::cout << " best differentiating rating vector alternative:\n";
    std::cout << "x = \n" << X << std::endl;
//    std::cout << "[Статья] x_1 = \n" << X_test_1.transpose() << std::endl;;
//    std::cout << "[Статья] x_2  = \n" << X_test_2.transpose() << std::endl;;


/* 3
 * Определение для заданных матриц A_1 , . . . , A_K парных сравнений
    N альтернатив и вектора весов w = (w_1 , . . . , w_K ) T наихудшего
    дифференцирующего вектора рейтингов альтернатив
 *
 * */
    std::cout << "3.\n";
//              "Определение для заданных матриц A_1 , . . . , A_K парных сравнений\n" <<
//              "N альтернатив и вектора весов w = (w_1 , . . . , w_K )^T наихудшего\n" <<
//              "дифференцирующего вектора рейтингов альтернатив\n";

/* 3.1
 * Вычисление взвешенной суммы матриц парных сравнений
 * */
    std::cout << "3.1\n";
    vector<MaxAlgMatrixXd> mat_R = Alternatives;
    for (auto i = 0; i < w.size(); ++i){
        mat_R[i] *= w(i);
    }
    MaxAlgMatrixXd R(mat_R.at(0).rows(),mat_R.at(0).cols());
    R.setIdentity();
    for (auto const & mat : mat_R){
        R += mat;
    }

    std::cout << "Matrix R = \n" << R << std::endl;

    /* 3.2
     *Построение генерирующей матрицы оптимальных рейтингов альтернатив
     * */

    std::cout << "3.2\n";
    double vu = SpectralRadius(R,"R");
    std::cout << "Spectral Radius R = " << vu << std::endl;
    MaxAlgMatrixXd S = Clini(d(1, vu) * R,"(vu^-1 * R)");
    std::cout << "Matrix Clini S = (v^-1 R)* = \n";
    std::cout << S << std::endl;



/* 3.3
 * Вычисление по матрице S наихудшего дифференцирующего вектора рейтингов альтернатив
 * */
    std::cout << "3.3\n";
//                 "Вычисление по матрице S наихудшего дифференцирующего\n" <<
//              "вектора рейтингов альтернатив\n";
    MaxAlgMatrixXd y = (I.transpose() * S).array().inverse().transpose();
    std::cout << "y = \n" << y << std::endl;

//    std::cout << "------------------Результаты---------------\n";
    std::cout << "best differentiating rating vector alternative:: x =\n" <<  X << std::endl;
    std::cout << "worst differentiating rating vector alternative:: y =\n" << y.cast<double>() << std::endl;

}

void TestMinMaxApprox(){
    {
        string hint = "5.1. Решение задачи о выборе места работы";
        //5.1. Решение задачи о выборе места работы"
        MaxAlgMatrixXd A1(3,3),A2(3,3),A3(3,3),A4(3,3),A5(3,3),A6(3,3);

        A1 << 1,d(1,4),d(1,2),
                4,1,3,
                2,d(1,3),1;
        A2 << 1,d(1,4),d(1,5),
                4,1,d(1,2),
                5,2,1;
        A3 << 1,3,d(1,3),
                d(1,3),1,1,
                3,1,1;
        A4 << 1,d(1,3),5,
                3,1,7,
                d(1,5),d(1,7),1;
        A5 << 1,1,7,
                1,1,7,
                d(1,7),d(1,7),1;
        A6 << 1,7,9,
                d(1,7),1,5,
                d(1,9),d(1,5),1;


        MaxAlgMatrixXd C(6, 6);
        C << 1, 1,1,4,1,d(1,2),
                1,1,2,4,1,d(1,2),
                1,d(1,2),1,5,3,d(1,2),
                d(1,4),d(1,4),d(1,5),1,d(1,3),d(1,3),
                1,1,d(1,3),3,1,1,
                2,2,2,3,1,1;

        MinMaxLogApprox({A1,A2,A3,A4,A5,A6},C,hint);
    }
    {
        //  Решение задачи 5.2
        string hint = "Решение задачи 5.2";
        MaxAlgMatrixXd A1(4,4),A2(4,4),A3(4,4),A4(4,4),A5(4,4);
        A1 << 1,d(1,2),1,d(1,2),
                2,1,d(5,2),1,
                1,d(2,5),1,d(2,5),
                2,1,d(5,2),1;
        A2 << 1,2,d(1,3),4,
                d(1,2),1,d(1,8),2,
                3,8,1,9,
                d(1,4),d(1,2),d(1,9),1;
        A3 << 1,5,d(1,2),d(5,2),
                d(1,5),1,d(1,9),d(1,4),
                2,9,1,7,
                d(2,5),4,d(1,7),1;
        A4 << 1,d(1,2),3,4,
                2,1,6,8,
                d(1,3),d(1,6),1,1,
                d(1,4),d(1,8),1,1;
        A5 << 1,d(3,2),d(1,2),4,
                d(2,3),1,d(2,7),d(5,2),
                2,d(7,2),1,9,
                d(1,4),d(2,5),d(1,9),1;



        MaxAlgMatrixXd C(5, 5);
        C << 1,d(1,5),3,d(1,2),5,
                5,1,7,1,7,
                d(1,3),d(1,7),1,d(1,4),3,
                2,1,4,1,7,
                d(1,5),d(1,7),d(1,3),d(1,7),1;


        MinMaxLogApprox({A1,A2,A3,A4,A5},C,hint);
    }


}
int main() {

    //TestMinMaxApprox();
//    TestRunner tr;
//    tr.RunTest(TestMatrixAddition,"TestMatrixAddition");
//    tr.RunTest(TestMatrixMultiplication,"TestMatrixMultiplication");
//    tr.RunTest(TestCliniMatrix,"TestCliniMatrix");
//    tr.RunTest(TestSpectralRadius,"TestSpectralRadius");
//
//
//    TestMinMaxApprox();
    {
        MaxAlgMatrixXd A1(3, 3), A2(3, 3), C(2, 2), I(2, 2);
        A1 << 1, 3, 2,
                d(1, 3), 1, d(1, 4),
                d(1, 2), 4, 1;
        A2 << 1, 4, 5,
                d(1, 4), 1, d(1, 3),
                d(1, 5), 3, 1;
//        C << 1,4,2,
//                d(1,4),1,d(1,3),
//                d(1,2),3,1;
        C << 1, 5,
                d(1, 5), 1;
        I.setIdentity();


//        Power(C,2,"C");
//        double lambda = SpectralRadius(C,"C");
        MinMaxLogApprox({A1, A2}, C, "");




//    << Power(Tr(Power(C,2)),1/2) << " " <<  Tr(Power(C,3))
//    std::cout << C.trace() << " " << pow(static_cast<double>(Power(C,2).trace()),1./2) << " " <<
//    pow(static_cast<double>(Power(C,3).trace()),1./3) << std::endl;
//    std::cout << (I + ( 1./3 * C) + 1./9 * Power(C,2)).cast<double>()<< std::endl;
//    std::cout << Clini(1./3 * C) << std::endl;
//    std::cout << (Power(C,2)).cast<double>() << std::endl;

    }
    return 0;
}


