#include "../include/method.h"
#include "../include/tropical.h"



int get_best_differentiating_weight_vector_index(const MaxAlgMatrixXd & D){

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

MaxAlgMatrixXd get_best_differentiating_weight_vector(const MaxAlgMatrixXd &D, int index) {
    MaxAlgMatrixXd v = D.col(index) * d(1,static_cast<double>(D.col(index).sum()));
    return v;
}

MaxAlgMatrixXd construction_generating_matrix_optimal_weights(const MaxAlgMatrixXd & Criteria,double lambda){
    MaxAlgMatrixXd D = Clini(d(1, lambda) * Criteria,"(1/lambda * C)");
    return D;
}

MaxAlgMatrixXd get_worst_differentiating_weight_vector(const MaxAlgMatrixXd &D) {
    MaxAlgVectorXd I(D.rows());
    I.setOnes();

    MaxAlgMatrixXd w = (I.transpose() * D).array().inverse();
    return w;
}
