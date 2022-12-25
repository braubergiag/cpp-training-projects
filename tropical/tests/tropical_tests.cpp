#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../include/max_algebra.h"
#include "../include/tropical.h"

using MaxAlgMatrixXd = MaxAlgMatrix<double ,Eigen::Dynamic,Eigen::Dynamic>;
using MaxAlgVectorXd = MaxAlgMatrix<double, Eigen::Dynamic,1>;
using MaxAlgArrayXXd = MaxAlgArray<double , Eigen::Dynamic, Eigen::Dynamic>;
using MaxAlgArrayXd = MaxAlgArray<double, Eigen::Dynamic,1>;

TEST(TropicalModule, SpectralRadius){
    MaxAlgMatrixXd A1(4,4);

    A1 << 1,3,4,2,
         d(1,3),1,d(1,2),d(1,3),
         d(1,4),2,1,4,
         d(1,2),3,d(1,4),1;

    ASSERT_EQ(SpectralRadius(A1), 2.0);


}

TEST(TropicalModule, Clini){

    MaxAlgMatrixXd  A1(4,4), A_clini(4,4);

    A1 << d(1,2), d(3,2), 2, 1,
        d(1,6),d(1,2),d(1,4),d(1,6),
        d(1,8),1,d(1,2),2,
        d(1,4),d(3,2),d(1,8),d(1,2);

    A_clini <<  1,6,2,4,
                d(1,6),1,d(1,3),d(2,3),
                d(1,2),3,1,2,
                d(1,4),d(3,2),d(1,2),1;


    ASSERT_EQ(Clini(A1),A_clini);

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