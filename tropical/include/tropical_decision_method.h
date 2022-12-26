
#ifndef TROPICAL_TROPICAL_DECISION_METHOD_H
#define TROPICAL_TROPICAL_DECISION_METHOD_H

#include "decision_method.h"
#include "tropical.h"



class tropical_decision_method : public decision_method{

public:
    tropical_decision_method(const vector<MaxAlgMatrixXd> &alternatives, const MaxAlgMatrixXd &criteria);

public:
    void perform() const override;

public:

    const vector<MaxAlgMatrixXd> &get_alternatives() const;
    const MaxAlgMatrixXd &get_criteria() const;

    void set_criteria(const MaxAlgMatrixXd &criteria);
    void set_alternatives(const vector<MaxAlgMatrixXd> &alternatives);

private:
    std::vector<MaxAlgMatrixXd>  alternatives_;
    MaxAlgMatrixXd criteria_;
};


#endif //TROPICAL_TROPICAL_DECISION_METHOD_H
