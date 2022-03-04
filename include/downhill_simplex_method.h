#pragma once

//My includes
#include <vector>
#include <functional>
#include <cmath>

typedef std::vector<double> dvector;

std::vector<dvector> downhill_simplex_method(const std::function<double(const dvector&)>& Q, 
                                            std::vector<dvector> initial_vector_X, const double eps,
                                            double reflection, double stretching, double compression);