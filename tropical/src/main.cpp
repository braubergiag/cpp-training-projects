
#include <iostream>

#include <Eigen/Dense>
#include <vector>
#include "../include/max_algebra.h"
#include "../include/tropical.h"
#include "../include/method.h"

using namespace Eigen;
using namespace std;




void MinMaxLogApprox(const std::vector<MaxAlgMatrixXd> & Alternatives, const MaxAlgMatrixXd & Criteria, const string & hint){


    double lambda = SpectralRadius(Criteria, "C");
    MaxAlgMatrixXd D = construction_generating_matrix_optimal_weights(Criteria,lambda);
    std::cout << "D = \n" << D << std::endl;

    int l_ = get_best_differentiating_weight_vector_index(D);
    std::cout << " Index l = " <<      l_ << std::endl;
    MaxAlgMatrixXd v = get_best_differentiating_weight_vector(D, l_);
    std::cout << "v = \n" << v << std::endl;


    MaxAlgMatrixXd w = get_worst_differentiating_weight_vector(D);
    std::cout << "w = " << w.cast<double>() << std::endl;


    std::cout << "2.1\n";

    MaxAlgMatrixXd P = computing_weighted_sum_pairwise_comparison_matrices(Alternatives,v);
    std::cout << "Matrix P = \n" << P << std::endl;



    std::cout << "2.2.\n";
    MaxAlgMatrixXd Q = build_generating_matrix_optimal_ratings_alternatives(P);
    std::cout << " Matrix Clini Q = (mu^-1 P)* = \n";
    std::cout << Q << std::endl;


    std::cout << " 2.3\n";
    MaxAlgMatrixXd X = calc_best_differentiating_vector_ratings_alternatives(D, Q, l_);
    std::cout << " best differentiating rating vector alternative:\n";
    std::cout << "x = \n" << X << std::endl;


    std::cout << "3.\n";
    std::cout << "3.1\n";
    MaxAlgMatrixXd R = computing_weighted_sum_pairwise_comparison_matrices(Alternatives,w);

    std::cout << "Matrix R = \n" << R << std::endl;

    std::cout << "3.2\n";
    MaxAlgMatrixXd S = build_generating_matrix_optimal_ratings_alternatives(R);

//    std::cout << "Spectral Radius R = " << vu << std::endl;
//    MaxAlgMatrixXd S = Clini(d(1, vu) * R,"(vu^-1 * R)");
    std::cout << "Matrix Clini S = (v^-1 R)* = \n";
    std::cout << S << std::endl;


    std::cout << "3.3\n";


    MaxAlgMatrixXd y = calc_worst_differentiating_vector_ratings_alternatives(S);

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
int main()
{

    TestMinMaxApprox();
//    TestRunner tr;
//    tr.RunTest(TestMatrixAddition,"TestMatrixAddition");
//    tr.RunTest(TestMatrixMultiplication,"TestMatrixMultiplication");
//    tr.RunTest(TestCliniMatrix,"TestCliniMatrix");
//    tr.RunTest(TestSpectralRadius,"TestSpectralRadius");
//
//
//    TestMinMaxApprox();





    return 0;
}


