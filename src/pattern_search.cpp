#include "pattern_search.h"

std::any pattern_search(const std::function<double(const dvector&)>& Q, const double eps, const double h,
                        const dvector& X_0, const dvector& delta)
{
    dvector cur_delta = delta;
    dvector T_2, T_1, T_1p, T_1m, T_2p, T_2m;
    dvector T = X_0;
    dvector X_1, X_2;
    bool flag;

    do 
    {
        X_1 = T_1 = T_2 = {0, 0};
        T_1p = { T[0] + delta[0], T[1] };
        T_1m = { T[0] - delta[0], T[1] };

        if (Q(T_1m) < Q(T))
        {
            T_1 = T_1m;
            flag = true;
        } 
        else if (Q(T_1p) < Q(T))
        {
            T_1 = T_1p;
            flag = true;
        }  else
        {
            T_1 = T;
        }

        T_2p = { T_1[0], T_1[1] + delta[1] };
        T_2m = { T_1[0], T_1[1] - delta[1] };

        if (Q(T_2p) < Q(T_1))
        {
            T_2 = T_2p;
            flag = true;
        } 
        else if (Q(T_2m) < Q(T_1))
        {
            T_2 = T_2m;
            flag = true;
        } else
        {
            T_2 = T_1;
        }

        X_1[0] = T[0] + h * (T_2[0] - T[0]);
        X_1[1] = T[1] + h * (T_2[1] - T[1]);
        
        if (Q(X_1) < Q(T))
        {
            T = X_1;
        }
        else
        {
            T = T_2;
        }

        if (!flag)
        {
            cur_delta[0] = (cur_delta[0] > 0.001) ? cur_delta[0] - 0.001 : cur_delta[0];
            cur_delta[1] = (cur_delta[1] > 0.001) ? cur_delta[1] - 0.001 : cur_delta[1];
        }
        flag = false;
    }
    while (cur_delta[0] > eps || cur_delta[1] > eps);

    return T;
}
