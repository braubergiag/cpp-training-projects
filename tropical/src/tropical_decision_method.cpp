
#include "../include/tropical_decision_method.h"

tropical_decision_method::tropical_decision_method(const vector<MaxAlgMatrixXd> &alternatives,
                                                   const MaxAlgMatrixXd &criteria) : alternatives_(alternatives),
                                                                                     criteria_(criteria) {}

const vector<MaxAlgMatrixXd> &tropical_decision_method::get_alternatives() const {
    return alternatives_;
}

void tropical_decision_method::set_alternatives(const vector<MaxAlgMatrixXd> &alternatives) {
    alternatives_ = alternatives;
}

const MaxAlgMatrixXd &tropical_decision_method::get_criteria() const {
    return criteria_;
}

void tropical_decision_method::set_criteria(const MaxAlgMatrixXd &criteria) {
    criteria_ = criteria;
}

void tropical_decision_method::perform() const {

}
