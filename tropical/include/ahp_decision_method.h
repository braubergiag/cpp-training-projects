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

public:
    void perform() const override;

public:
    ahp_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const MatrixXd &criteria);

};


#endif //TROPICAL_AHPDECISIONMETHOD_H
