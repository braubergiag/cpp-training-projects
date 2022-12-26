//
// Created by igor on 26.12.22.
//

#include "../include/decision.h"

std::map<std::vector<std::string>, VectorXd> decision::sortAlternatives(std::vector<std::string> alternatives) {

    std::map<std::vector<std::string>, VectorXd> decision;
    for (int i = 0; i < m_critWeights.size(); ++i)
    {
        double crit_weight = m_critWeights[i];
        std::string altern =  alternatives[i];
        int j = i - 1;
        while (j >= 0 && crit_weight >m_critWeights[j])
        {
            m_critWeights[j + 1] = m_critWeights[j];
            alternatives[j + 1] = alternatives[j];
            j -= 1;
        }
        m_critWeights[j + 1] = crit_weight;
        alternatives[j + 1] = altern;
    }
    decision.insert(std::pair(alternatives,m_critWeights));
    return decision;
}
