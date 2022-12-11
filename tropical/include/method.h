//
// Created by igor on 11.12.22.
//

#ifndef TROPICAL_METHOD_H
#define TROPICAL_METHOD_H


#include "tropical.h"

int get_best_differentiating_weight_vector_index(const MaxAlgMatrixXd & D);
MaxAlgMatrixXd get_best_differentiating_weight_vector(const MaxAlgMatrixXd & D, int index);
MaxAlgMatrixXd get_worst_differentiating_weight_vector(const MaxAlgMatrixXd & D);
MaxAlgMatrixXd construction_generating_matrix_optimal_weights(const MaxAlgMatrixXd & Criteria,double lambda);

#endif //TROPICAL_METHOD_H
