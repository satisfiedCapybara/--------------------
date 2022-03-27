#include "downhill_simplex_method.h"

std::any downhill_simplex_method(const std::function<double(const dvector&)>& Q, 
                                std::vector<dvector> initial_vector_X, const double eps = 0.001,
                                const double reflection = 1, const double stretching = 2, const double compression = 0.5)
{
    std::vector<dvector> cur_vector_X = initial_vector_X;
    int vector_size = cur_vector_X.size();
    int size = cur_vector_X.back().size();

    while (true)
    {
        std::sort(begin(cur_vector_X), end(cur_vector_X),
        [&Q] (const dvector& first, const dvector& second) 
        { 
            return Q(first) < Q(second); 
        });

        dvector gravity_center(size, 0);
        for(size_t i = 0; i < size; ++i)
        {
            for(size_t j = 0; j < vector_size; ++j)
            {
                gravity_center[i] += cur_vector_X[j][i];
            }
            gravity_center[i] /= size;
        }

        dvector reflection_X(size, 0);
        for(size_t i = 0; i < size; ++i)
        {
            reflection_X[i] = gravity_center[i] + reflection * (gravity_center[i] - cur_vector_X.back()[i]);
        }

        if (Q(cur_vector_X.front()) <= Q(reflection_X) && Q(reflection_X) <= Q(cur_vector_X[size - 2]))
        {
            cur_vector_X.back() = reflection_X;
        }
        else if (Q(reflection_X) < Q(cur_vector_X.front()))
        {
            dvector stretching_X(size, 0);
            for(size_t i = 0; i < size; ++i)
            {
                stretching_X[i] = gravity_center[i] + stretching * (reflection_X[i] - gravity_center[i]);
            }
            cur_vector_X.front() = stretching_X;
        }
        else if (Q(reflection_X) > Q(cur_vector_X[size - 2]))
        {
            dvector compression_X(size,0);
            for(size_t i = 0; i < size; ++i)
            {
                if (Q(reflection_X) < Q(cur_vector_X.back()))
                {
                    compression_X[i] = gravity_center[i] + compression * (reflection_X[i] - gravity_center[i]);
                }
                else
                {
                    compression_X[i] = gravity_center[i] + compression * (cur_vector_X.back()[i] - gravity_center[i]);
                }
            }

            if (Q(compression_X) < std::min<double>(Q(cur_vector_X.back()), Q(reflection_X)))
            {
                cur_vector_X.back() = compression_X;
            }
            else
            {
                for(size_t i = 0; i < vector_size; ++i)
                {
                    for(size_t j = 0; j < size; ++j)
                    {
                        cur_vector_X[i][j] = (cur_vector_X[i][j] + cur_vector_X.front()[j]) / 2;
                    }
                }
            }
        }

        double polygon_size = 0;
        for(size_t i = 0; i < vector_size; ++i)
        {
            polygon_size += std::pow(Q(cur_vector_X[i]) - Q(cur_vector_X.front()), 2);
        }
        polygon_size = sqrt(polygon_size / vector_size);

        if (polygon_size < eps)
        {
            break;
        }
    }

    return cur_vector_X;
}