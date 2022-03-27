//STL includes
#include <any>
#include <cmath>
#include <iostream>

//My includes
#include "downhill_simplex_method.h"
#include "pattern_search.h"

using namespace std;

int main() {
    //Initial parameters for pattern_search
    dvector X = {-1.0, 2.0 };
    dvector delta = {1, 1};
    double eps = 0.01;
    double h = 1;

    //Optimization function
    auto Q = [] (const dvector& vec) 
    { 
        return 100 * (pow(vec[0]*vec[0] - vec[1], 2) + pow(1 - vec[0], 2));
    };

    //Initial parameters for downhill simplex method:
    vector<dvector> initial_vector({ {1, 0.5}, {-0.4, 1.2}, {1.4, 1.4} });
    double reflection = 1;
    double stretching = 2;
    double compression = 0.9;

    try
    {
        auto sln_vector_dsm = any_cast<vector<dvector>>(downhill_simplex_method(Q, initial_vector, eps, reflection, stretching, compression));      
        auto sln_ps = any_cast<dvector>(pattern_search(Q, 2, X, delta, 0.00001, h));

        cout << "Pattern search:" << endl;
        cout << "X = { ";
        for (int i = 0; i < 2; ++i)
        {
            cout << sln_ps[i] << " ";
        }
        cout << "}" << endl;
        cout << "Q = " << Q(sln_ps) << endl;

        cout << "Downhill simplex method:" << endl;
        cout << "X = { ";
        for (int i = 0; i < 2; ++i)
        {
            cout << sln_vector_dsm.front()[i] << " ";
        }
        cout << "}" << endl;
        cout << "Q = " << Q(sln_ps)<< endl;

    }
    catch(const bad_any_cast& ex)
    {
        cerr << ex.what() << '\n';
    }
    
    return 0;
}
