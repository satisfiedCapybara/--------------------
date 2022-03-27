//STL includes
#include <any>
#include <cmath>
#include <iostream>

//My includes
#include "downhill_simplex_method.h"
#include "pattern_search.h"

using namespace std;

int main() {
    //Common parameters
    dvector delta = {1, 1};
    double eps = 0.01;
    double h = 1;
    double reflection = 1;
    double stretching = 2;
    double compression = 0.9;

    //Initial parameters for pattern_search Q_0
    dvector X_0 = {-1.0, 2.0 };

    //Initial parameters for pattern_search Q_1
    dvector X_1 = {-1.2, -1 };

    //Initial parameters for pattern_search Q_2
    dvector X_2 = {-1.2, 1 };

    //Initial parameters for pattern_search Q_3
    dvector X_3 = { 3, -1, 0, 1 };

    //Initial parameters for downhill simplex method 0:
    vector<dvector> initial_vector_0({ {1, 0.5}, {-0.4, 1.2}, {1.4, 1.4} });

    //Initial parameters for downhill simplex method 1:
    vector<dvector> initial_vector_1({ {1, 0.5}, {-0.1, 1.2}, {1.4, 1.4} });

    //Initial parameters for downhill simplex method 2:
    vector<dvector> initial_vector_2({ {-1.6, 0.6}, {-0.7, 1}, {-0.9, 0.5} });

    //Initial parameters for downhill simplex method 3:
    vector<dvector> initial_vector_3({ {0.5, 0, 0, 0}, {-0.5, 0.5, 0, 0}, {-0.5, 0, 0.5, 0}, {-0.5, 0, 0, 0.5} });

    //Optimization funtions
    auto Q_0 = [] (const dvector& vec) 
    { 
        return 100 * (pow(vec[0]*vec[0] - vec[1], 2) + pow(1 - vec[0], 2));
    }; 

    auto Q_1 = [] (const dvector& vec) 
    { 
        return 100 * (pow(pow(vec[0],2) - pow(vec[1],3), 2) + pow(1 - vec[0], 2));
    };

    auto Q_2 = [] (const dvector& vec) 
    { 
        return 100 * (pow(pow(vec[0],2) - pow(vec[1],3), 2) + pow(1 + vec[0], 2));
    };

    auto Q_3 = [] (const dvector& vec) 
    { 
        return (pow(vec[0] + 10 * vec[1], 2) + 5 * pow(vec[2] - vec[3], 2) + pow(vec[1] - 2*vec[2], 4) + 10 * pow(vec[0] - vec[3], 4));
    };   

    try
    {
        auto sln_vector_dsm_0 = any_cast<vector<dvector>>(downhill_simplex_method(Q_0, initial_vector_0, eps, reflection, stretching, compression));
        auto sln_vector_dsm_1 = any_cast<vector<dvector>>(downhill_simplex_method(Q_1, initial_vector_1, eps, reflection, stretching, compression));
        auto sln_vector_dsm_2 = any_cast<vector<dvector>>(downhill_simplex_method(Q_2, initial_vector_2, eps, reflection, stretching, compression));
        auto sln_vector_dsm_3 = any_cast<vector<dvector>>(downhill_simplex_method(Q_3, initial_vector_3, eps, reflection, stretching, compression));      
        auto sln_ps_0 = any_cast<dvector>(pattern_search(Q_0, 2, X_0, delta, eps, h));
        auto sln_ps_1 = any_cast<dvector>(pattern_search(Q_1, 2, X_1, delta, eps, h));
        auto sln_ps_2 = any_cast<dvector>(pattern_search(Q_2, 2, X_2, delta, eps, h));
        auto sln_ps_3 = any_cast<dvector>(pattern_search(Q_3, 4, X_3, {1, 1, 1, 1}, eps, h));

        cout << "Pattern search:" << endl;
        cout << "X_0 = { ";
        for (int i = 0; i < 2; ++i)
        {
            cout << sln_ps_0[i] << " ";
        }
        cout << "}" << endl;
        cout << "Q_0 = " << Q_0(sln_ps_0) << endl;

        cout << "Pattern search:" << endl;
        cout << "X_1 = { ";
        for (int i = 0; i < 2; ++i)
        {
            cout << sln_ps_1[i] << " ";
        }
        cout << "}" << endl;
        cout << "Q_1 = " << Q_1(sln_ps_1) << endl;

        cout << "Pattern search:" << endl;
        cout << "X_2 = { ";
        for (int i = 0; i < 2; ++i)
        {
            cout << sln_ps_2[i] << " ";
        }
        cout << "}" << endl;
        cout << "Q_2 = " << Q_2(sln_ps_2) << endl;

        cout << "Pattern search:" << endl;
        cout << "X_3 = { ";
        for (int i = 0; i < 4; ++i)
        {
            cout << sln_ps_3[i] << " ";
        }
        cout << "}" << endl;
        cout << "Q_3 = " << Q_3(sln_ps_3) << endl;           

        cout << "Downhill simplex method:" << endl;
        cout << "X_0 = { ";
        for (int i = 0; i < 2; ++i)
        {
            cout << sln_vector_dsm_0.front()[i] << " ";
        }
        cout << "}" << endl;
        cout << "Q_0 = " << Q_0(sln_vector_dsm_0.front())<< endl;

        cout << "Downhill simplex method:" << endl;
        cout << "X_1 = { ";
        for (int i = 0; i < 2; ++i)
        {
            cout << sln_vector_dsm_1.front()[i] << " ";
        }
        cout << "}" << endl;
        cout << "Q_1 = " << Q_0(sln_vector_dsm_1.front())<< endl;


        cout << "Downhill simplex method:" << endl;
        cout << "X_2 = { ";
        for (int i = 0; i < 2; ++i)
        {
            cout << sln_vector_dsm_2.front()[i] << " ";
        }
        cout << "}" << endl;
        cout << "Q_2 = " << Q_2(sln_vector_dsm_2.front())<< endl;

        cout << "Downhill simplex method:" << endl;
        cout << "X_3 = { ";
        for (int i = 0; i < 4; ++i)
        {
            cout << sln_vector_dsm_3.front()[i] << " ";
        }
        cout << "}" << endl;
        cout << "Q_3 = " << Q_3(sln_vector_dsm_3.front())<< endl;
    }
    catch(const bad_any_cast& ex)
    {
        cerr << ex.what() << '\n';
    }
    
    return 0;
}
