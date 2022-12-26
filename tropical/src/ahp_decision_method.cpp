//
// Created by igor on 26.12.22.
//

#include "../include/ahp_decision_method.h"
#include <Eigen/Eigenvalues>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::EigenSolver;


ahp_decision_method::ahp_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const MatrixXd &criteria)
        : heuristic_decision_method(alternatives, criteria) {}

void ahp_decision_method::perform() const {
    const int alter_num = get_alternatives().at(0).rows();
    const int criter_num = get_criteria().rows();
    MatrixXd matrix_weights,matrix_norm_weights;

    VectorXd crit_vector = VectorXd::Ones(criter_num);
    VectorXd final_weights = VectorXd::Ones(alter_num);
    EigenSolver<MatrixXd> critEigSolver(get_criteria());
    matrix_weights.setZero(alter_num,criter_num);
    matrix_norm_weights.setZero(alter_num,criter_num);
    double lambda = 0;
    std::vector<EigenSolver< MatrixXd >>  VEC;
    for (int i = 0; i < criter_num; ++i) {
        crit_vector(i) = abs(real(critEigSolver.eigenvectors().col(0)(i, 0)));

        VEC.push_back(EigenSolver<MatrixXd>(get_alternatives().at(i) ));
        for (int j = 0; j < alter_num; ++j) {
            matrix_weights(j,i) = abs(real(VEC.at(i).eigenvectors().col(0)(j, 0)));
        }
    }
    double critVectSum = crit_vector.sum();
    for (int i = 0; i < criter_num; ++i) {
        crit_vector(i) /= critVectSum;
        for (int j = 0; j < alter_num; ++j) {
            matrix_norm_weights(j, i) = matrix_weights(j, i) / matrix_weights.col(i).sum();

        }
    }
    final_weights = matrix_norm_weights * crit_vector;
//    Decision d(matrix_norm_weights,final_weights);
//    return d;

}
