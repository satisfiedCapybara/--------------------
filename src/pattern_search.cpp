//My includes
#include "pattern_search.h"

#define DELTA_STEP 0.00001

std::any pattern_search(const std::function<double(const dvector&)>& Q, int dimension, const dvector& initial_X,
                        const dvector& delta, const double eps = 0.001, const double h = 1)
{
    dvector current_delta = delta, current_Xp, current_Xm;
    dvector current_X = initial_X, candidate_X = current_X;
    dvector previous_X;

    double max_delta;

    do 
    {
        previous_X = current_X;
        current_Xp = current_X;
        current_Xm = current_X;

        for (int i = 0; i < dimension; ++i)
        {
            current_Xm[i] = current_X[i] - current_delta[i];
            current_Xp[i] = current_X[i] + current_delta[i];

            if (Q(current_Xm) < Q(current_X))
            {
                current_X = current_Xm;
            } else if (Q(current_Xp) < Q(current_X))
            {
                current_X = current_Xp;
            }
        }

        for (int i = 0; i < dimension; ++i)
        {
            candidate_X[i] = candidate_X[i] + h *(current_X[i] - candidate_X[i]);
        }
        
        if (Q(candidate_X) < Q(current_X))
        {
            current_X = candidate_X;
        }

        if (previous_X == current_X)
        {
            for (int i = 0; i < dimension; ++i)
            {
                current_delta[i] = (current_delta[i] > DELTA_STEP) ? current_delta[i] - DELTA_STEP : current_delta[i];
            }
        }
        max_delta = *std::max_element(std::begin(current_delta), std::end(current_delta));
    }
    while (max_delta > eps);

    return current_X;
}
