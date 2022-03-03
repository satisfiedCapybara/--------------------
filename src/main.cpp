//STL includes
#include <any>
#include <cmath>
#include <iostream>

//My includes
#include "pattern_search.h"

int main() {
    //Initial parameters
    dvector X = {-1.0, 2.0 };
    dvector delta = {2, 1};
    double eps = 0.001;
    double h = 1;

    //Optimization function
    auto Q = [] (const dvector& vec) 
    { 
        return 100 * (std::pow(vec[0]*vec[0] - vec[1], 2) + std::pow(1 - vec[0], 2));
    };

    try
    {
        dvector sln = std::any_cast<dvector>(pattern_search(Q, eps, h, X, delta));
        std::cout << "X = { " << sln[0] << ", " << sln[1] << " }" << std::endl;
    }
    catch(const std::bad_any_cast& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
