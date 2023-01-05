#include "../include/ahp_decision_method.h"
#include <Eigen/Eigenvalues>
#include <iostream>
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::EigenSolver;


ahp_decision_method::ahp_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const MatrixXd &criteria)
        : heuristic_decision_method(alternatives, criteria) {}



Eigen::MatrixXcd ahp_decision_method::get_main_eigenvector(const MatrixXd &matrix) const {
    EigenSolver<MatrixXd> eigen_solver(matrix);
    Eigen::MatrixXcd eigen_vector = eigen_solver.eigenvectors().col(0).real();
    double sum = eigen_vector.cwiseAbs().sum();
    for (size_t i = 0, rows_count = eigen_vector.rows(); i < rows_count; ++i) {
        eigen_vector.coeffRef(i) = abs(eigen_vector.coeffRef(i) / sum);
    }
    return eigen_vector.real();
}


Eigen::MatrixXd
ahp_decision_method::get_weight_matrix(const std::vector<Eigen::MatrixXcd> &alternatives_main_eigen_vectors) const {

    Eigen::MatrixXd weights(get_alternatives_count(),get_criteria_count());
    for (int i = 0; i < get_criteria_count(); ++i){
        for (int j = 0; j < get_alternatives_count(); ++j) {
            weights(j,i) = alternatives_main_eigen_vectors.at(i).coeff(j).real();
        }

    }

    return weights;
}

Eigen::VectorXd ahp_decision_method::get_weight_vector(const Eigen::VectorXcd &criteria_main_eigen_vector,
                                                       const std::vector<Eigen::MatrixXcd> &alternatives_main_eigen_vectors) const {
    return (get_weight_matrix(alternatives_main_eigen_vectors) * criteria_main_eigen_vector).real();
}

void ahp_decision_method::perform() const  {

    Eigen::VectorXcd criteria_main_eigen_vector = get_main_eigenvector(get_criteria());
    std::vector<Eigen::MatrixXcd> alternatives_main_eigen_vectors;
    std::transform(get_alternatives().begin(),
                   get_alternatives().end(),
                   std::back_inserter(alternatives_main_eigen_vectors),
                   [this](const auto & alter_matrix){
                       return get_main_eigenvector(alter_matrix);
                   });




}
