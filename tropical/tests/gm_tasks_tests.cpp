#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../include/gm_decision_method.h"
inline double d(double p, double q) {
    // Assert(q != 0, "Division by zero");
    return p / q;
}

using Eigen::VectorXd;
using Eigen::MatrixXcd;
using Eigen::MatrixXd;

TEST(GmModule,Task_5_1) {
    //5.1. Решение задачи о выборе места работы"
    MatrixXd A1(3,3),A2(3,3),A3(3,3),A4(3,3),A5(3,3),A6(3,3);

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


    MatrixXd C(6, 6);
    C << 1, 1,1,4,1,d(1,2),
            1,1,2,4,1,d(1,2),
            1,d(1,2),1,5,3,d(1,2),
            d(1,4),d(1,4),d(1,5),1,d(1,3),d(1,3),
            1,1,d(1,3),3,1,1,
            2,2,2,3,1,1;


    gm_decision_method gm_model({A1,A2,A3,A4,A5,A6},C);
    double eps = 0.01;

    gm_model.perform();

    Eigen::MatrixXd final_weights(1,3);
    final_weights <<  0.3843 ,0.3516 ,0.2641;

//    ASSERT_NEAR(ahp_model.get_weight_vector().norm(), final_weights.norm(), eps);




}