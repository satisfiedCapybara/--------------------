//STL includes
#include <any>
#include <cmath>
#include <iostream>

//My includes
#include "downhill_simplex_method.h"
#include "pattern_search.h"

int main() {
    //Initial parameters for pattern_search
    dvector X = {-1.0, 2.0 };
    dvector delta = {2, 1};
    double eps = 0.01;
    double h = 1;

    //Optimization function
    auto Q = [] (const dvector& vec) 
    { 
        return 100 * (std::pow(vec[0]*vec[0] - vec[1], 2) + std::pow(1 - vec[0], 2));
    };

    //Initial parameters for 
    std::vector<dvector> initial_vector({ {1, 0.5}, {-0.4, 1.2}, {1.4, 1.4} });
    double reflection = 1;
    double stretching = 2;
    double compression = 0.9;

    dvector sln_vector_dsm = downhill_simplex_method(Q, initial_vector, eps, reflection, stretching, compression).front();

    try
    {
        dvector sln_ps = std::any_cast<dvector>(pattern_search(Q, eps, h, X, delta));

        std::cout << "Pattern search:" << std::endl;
        std::cout << "X = { " << sln_ps[0] << ", " << sln_ps[1] << " }" << std::endl;

        std::cout << "Downhill simplex method:" << std::endl;
        std::cout << "X = { " << sln_vector_dsm[0] << ", " << sln_vector_dsm[1] << " }" << std::endl;

    }
    catch(const std::bad_any_cast& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
