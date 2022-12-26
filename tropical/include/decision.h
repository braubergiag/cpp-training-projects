//
// Created by igor on 26.12.22.
//

#ifndef TROPICAL_DECISION_H
#define TROPICAL_DECISION_H

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <vector>
#include <map>
#include <string>
using Eigen::MatrixXd;
using Eigen::VectorXd;

class decision {
        MatrixXd m_weights;
        VectorXd m_critWeights;
    public:
        decision(MatrixXd weights,VectorXd critWeights):
        m_weights(weights),m_critWeights(critWeights){};
        MatrixXd getMatrix() const {return m_weights;};
        VectorXd getWeights() const {return m_critWeights;};
        VectorXd sortWeights() const;
        std::map<std::vector<std::string>,VectorXd> sortAlternatives(std::vector<std::string> alternatives);
    };


#endif //TROPICAL_DECISION_H
