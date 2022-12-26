//
// Created by igor on 26.12.22.
//

#include "../include/ahp_decision_method.h"


ahp_decision_method::ahp_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const MatrixXd &criteria)
        : heuristic_decision_method(alternatives, criteria) {}

void ahp_decision_method::perform() const {

}
