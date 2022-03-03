#pragma once

#include <vector>
#include <any>
#include <functional>

typedef std::vector<double> dvector;

std::any pattern_search(const std::function<double(const dvector&)>& Q, const double eps, const double h,
                        const dvector& X_0, const dvector& delta);