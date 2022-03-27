//My includes
#include "pattern_search.h"
#include <iostream>

#define EPS_DELTA 0.00001

std::any pattern_search(const std::function<double(const dvector&)>& Q, int dimension, const dvector& X_0, const dvector& delta,
                        const double eps = 0.01, const double h = 1)
{
    dvector cur_delta = delta;
    dvector T_p, T_m;
    dvector T = X_0;
    dvector X_1 = T;
    bool flag;

    do 
    {
        dvector previous_X = T;
        T_p = T;
        T_m = T;

        for (int i = 0; i < dimension; ++i)
        {
            T_m[i] = T[i] - cur_delta[i];
            T_p[i] = T[i] + cur_delta[i];

            if (Q(T_m) < Q(T))
            {
                T = T_m;
            } else if (Q(T_p) < Q(T))
            {
                T = T_p;
            }
        }

        for (int i = 0; i < dimension; ++i)
        {
            X_1[i] = X_1[i] + h *(T[i] - X_1[i]);
        }
        
        if (Q(X_1) < Q(T))
        {
            T = X_1;
        }

        if (previous_X == T)
        {
            for (int i = 0; i < dimension; ++i)
            {
                cur_delta[i] = (cur_delta[i] > EPS_DELTA) ? cur_delta[i] - EPS_DELTA : cur_delta[i];
            }
        }
    }
    while (*std::max_element(std::begin(cur_delta), std::end(cur_delta)) > eps);

    return T;
}
