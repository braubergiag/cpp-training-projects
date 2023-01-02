//
// Created by igor on 26.12.22.
//

#ifndef TROPICAL_AHPDECISIONMETHOD_H
#define TROPICAL_AHPDECISIONMETHOD_H

#include <Eigen/Dense>
#include <vector>
#include "heuristic_decision_method.h"


using Eigen::MatrixXd;

class ahp_decision_method : public heuristic_decision_method {

private:
    std::vector<Eigen::MatrixXcd> alternatives_main_eigen_vectors_;
    Eigen::VectorXcd criteria_main_eigen_vector_;

public:
    Eigen::MatrixXd get_weight_matrix() const;
    void perform() const override;
    void perform_advanced() ;
    Eigen::MatrixXcd get_main_eigenvector(const MatrixXd & matrix) const;
    Eigen::VectorXd get_weight_vector() const;

    const std::vector<Eigen::MatrixXcd> &get_alternatives_main_eigen_vectors() const;

    const Eigen::VectorXcd &get_criteria_main_eigen_vector() const;

public:
    ahp_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const MatrixXd &criteria);

};


#endif //TROPICAL_AHPDECISIONMETHOD_H
