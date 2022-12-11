#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../include/max_algebra.h"
#include "../include/tropical.h"

using MaxAlgMatrixXd = MaxAlgMatrix<double ,Eigen::Dynamic,Eigen::Dynamic>;
using MaxAlgVectorXd = MaxAlgMatrix<double, Eigen::Dynamic,1>;
using MaxAlgArrayXXd = MaxAlgArray<double , Eigen::Dynamic, Eigen::Dynamic>;
using MaxAlgArrayXd = MaxAlgArray<double, Eigen::Dynamic,1>;

TEST(TropicalModule, SpectralRadius){



}

TEST(TropicalModule,Trace){
    MaxAlgMatrixXd A1(3,3),A2(3,3),A3(3,3),A4(3,3),A5(3,3),A6(3,3);

    A1 <<   1,2,3,
            4,5,3,
            2,4,2;
    ASSERT_EQ(A1.trace(), 5.0);


    A2 <<   d(1,2), 1,      1,
            1,      d(1,4), 1,
            1,      2,      d(1,5);
    ASSERT_EQ(A2.trace(), 0.5);

    A3 <<   100,1,  1,
            0,  10, 1,
            3,  1,  1;
    ASSERT_EQ(A3.trace(), 100.0);



}