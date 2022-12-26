//
// Created by igor on 26.12.22.
//

#include "../include/gm_decision_method.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

gm_decision_method::gm_decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
                                       const Eigen::MatrixXd &criteria) : heuristic_decision_method(alternatives,
                                                                                                    criteria) {}

void gm_decision_method::perform() const {
    const int alter_num = get_alternatives().at(0).rows();
    const int criter_num = get_criteria().rows();
    MatrixXd matrix_weights,matrix_powers,matrix_norm_weights;
    VectorXd crit_vector = VectorXd::Ones(criter_num);
    VectorXd final_weights= VectorXd::Ones(alter_num);


    matrix_weights.setZero(alter_num,criter_num);
    matrix_powers.setZero(alter_num,criter_num);
    matrix_norm_weights.setZero(alter_num,criter_num);

    for (int i = 0; i < criter_num; ++i) {
        crit_vector(i) =  pow(get_criteria().row(i).prod(), 1./criter_num);
        for (int j =0; j < alter_num; ++j){
            matrix_weights(j,i) = pow(get_alternatives().at(i).row(j).prod(),1./alter_num);
        }


    }
    double critVectorSum = crit_vector.sum();
    for (int i = 0; i < criter_num; ++i) {
        crit_vector(i) = crit_vector(i) / critVectorSum;
        for (int j = 0; j < alter_num; ++j) {
            matrix_norm_weights(j, i) = matrix_weights(j, i) / matrix_weights.col(i).sum();

        }
    }

    for (int i = 0; i < criter_num; ++i){
        for (int j = 0; j < alter_num; ++j) {
            matrix_powers(j,i) = pow(matrix_weights(j,i),crit_vector(i));
        }
    }
    for (int i =0; i < criter_num; ++i){
        for (int j =0; j < alter_num; ++j)
            final_weights(j) *= matrix_powers(j,i);
    }
    double finalVectorSum = final_weights.sum();
    for (int i =0; i < final_weights.size();++i)
        final_weights(i) /= finalVectorSum;

//    Decision d(matrix_weights,final_weights);
//    return d;
}
