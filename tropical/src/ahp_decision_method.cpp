//
// Created by igor on 26.12.22.
//

#include "../include/ahp_decision_method.h"
#include <Eigen/Eigenvalues>
#include <iostream>
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

    std::vector<EigenSolver< MatrixXd >>  VEC;
    for (int i = 0; i < criter_num; ++i) {
        crit_vector(i) = abs(real(critEigSolver.eigenvectors().col(0)(i, 0)));

        VEC.push_back(EigenSolver<MatrixXd>(get_alternatives().at(i) ));
        for (int j = 0; j < alter_num; ++j) {
            matrix_weights(j,i) = abs(real(VEC.at(i).eigenvectors().col(0)(j, 0)));
        }
    }


    matrix_norm_weights.setZero(alter_num,criter_num);
    double critVectSum = crit_vector.sum();
    for (int i = 0; i < criter_num; ++i) {
        crit_vector(i) /= critVectSum;
        for (int j = 0; j < alter_num; ++j) {
            matrix_norm_weights(j, i) = matrix_weights(j, i) / matrix_weights.col(i).sum();

        }
    }
    final_weights = matrix_norm_weights * crit_vector;
    std::cout << final_weights << "\n\n";
//    Decision d(matrix_norm_weights,final_weights);
//    return d;

}

Eigen::MatrixXcd ahp_decision_method::get_main_eigenvector(const MatrixXd &matrix) const {
    EigenSolver<MatrixXd> eigen_solver(matrix);
    Eigen::MatrixXcd eigen_vector = eigen_solver.eigenvectors().col(0).real();
    double sum = eigen_vector.cwiseAbs().sum();
    for (size_t i = 0, rows_count = eigen_vector.rows(); i < rows_count; ++i) {
        eigen_vector.coeffRef(i) = abs(eigen_vector.coeffRef(i) / sum);
    }
    return eigen_vector.real();
}


Eigen::MatrixXd ahp_decision_method::get_weight_matrix() const {

    Eigen::MatrixXd weights(get_alternatives_count(),get_criteria_count());
    for (int i = 0; i < get_criteria_count(); ++i){
        for (int j = 0; j < get_alternatives_count(); ++j) {
            weights(j,i) = alternatives_main_eigen_vectors_.at(i).coeff(j).real();
        }

    }

    return weights;
}

Eigen::VectorXd ahp_decision_method::get_weight_vector() const {
    return (get_weight_matrix() * criteria_main_eigen_vector_).real();
}

void ahp_decision_method::perform_advanced()  {
    criteria_main_eigen_vector_ = get_main_eigenvector(get_criteria());
    
    std::transform(get_alternatives().begin(),
                   get_alternatives().end(),
                   std::back_inserter(alternatives_main_eigen_vectors_),
                   [this](const auto & alter_matrix){
       return get_main_eigenvector(alter_matrix);
    });




}

const std::vector<Eigen::MatrixXcd> &ahp_decision_method::get_alternatives_main_eigen_vectors() const {
    return alternatives_main_eigen_vectors_;
}

const Eigen::VectorXcd &ahp_decision_method::get_criteria_main_eigen_vector() const {
    return criteria_main_eigen_vector_;
}
