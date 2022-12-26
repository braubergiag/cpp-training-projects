//
// Created by igor on 26.12.22.
//

#include "../include/gm_decision_method.h"

gm_decision_method::gm_decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
                                       const Eigen::MatrixXd &criteria) : heuristic_decision_method(alternatives,
                                                                                                    criteria) {}

void gm_decision_method::perform() const {

}
