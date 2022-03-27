#pragma once

//STL includes
#include <algorithm>
#include <vector>
#include <any>
#include <functional>

typedef std::vector<double> dvector;

std::any pattern_search(const std::function<double(const dvector&)>& Q, int dimension, const dvector& X_0, const dvector& delta,
                        const double eps, const double h);