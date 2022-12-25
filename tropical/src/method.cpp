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
    MaxAlgMatrixXd D = clini(d(1, lambda) * Criteria);
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
    double mu = spectral_radius(P, "P");
    MaxAlgMatrixXd Q = clini(d(1, mu) * P);
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
    // std::cout << " Index m = " << m_ << std::endl;
    MaxAlgMatrixXd X = Q.col(m_) * d(1,static_cast<double>(Q.col(index).sum()));
    return X;
}

MaxAlgMatrixXd calc_worst_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &S) {
    MaxAlgVectorXd I(S.rows());
    I.setOnes();
    MaxAlgMatrixXd y = (I.transpose() * S).array().inverse().transpose();
    return y;
}
void MinMaxLogApprox(const std::vector<MaxAlgMatrixXd> & Alternatives, const MaxAlgMatrixXd & Criteria, const string & hint){


    double lambda = spectral_radius(Criteria, "C");
    std::cout << lambda << "\n";
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
    std::cout << " Matrix clini Q = (mu^-1 P)* = \n";
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
    std::cout << "Matrix clini S = (v^-1 R)* = \n";
    std::cout << S << std::endl;


    std::cout << "3.3\n";


    MaxAlgMatrixXd y = calc_worst_differentiating_vector_ratings_alternatives(S);

    std::cout << "best differentiating rating vector alternative:: x =\n" <<  X << std::endl;
    std::cout << "worst differentiating rating vector alternative:: y =\n" << y.cast<double>() << std::endl;

}