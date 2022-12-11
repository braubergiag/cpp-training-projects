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

MaxAlgMatrixXd computing_weighted_sum_pairwise_comparison_matrices(std::vector<MaxAlgMatrixXd> alternatives,
                                                                   const MaxAlgMatrixXd &v) {
    for (auto i = 0; i < v.size(); ++i){
        alternatives[i] *= v(i);
    }
    MaxAlgMatrixXd P(alternatives.at(0).rows(), alternatives.at(0).cols());
    P.setIdentity();
    for (auto const & mat : alternatives){
        P += mat;
    }

    return P;
}

MaxAlgMatrixXd build_generating_matrix_optimal_ratings_alternatives(const MaxAlgMatrixXd &P) {
    double mu = SpectralRadius(P,"P");
    MaxAlgMatrixXd Q = Clini(d(1,mu) * P,"(mu^-1 P)");
    return Q;
}

MaxAlgMatrixXd
calc_best_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &D, const MaxAlgMatrixXd &Q, int index) {
    MaxAlgVectorXd I(D.rows());
    I.setOnes();
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
    MaxAlgMatrixXd X = Q.col(m_) * d(1,static_cast<double>(Q.col(index).sum()));
    return X;
}

MaxAlgMatrixXd calc_worst_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &S) {
    MaxAlgVectorXd I(S.rows());
    I.setOnes();
    MaxAlgMatrixXd y = (I.transpose() * S).array().inverse().transpose();
    return y;
}
