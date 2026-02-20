/// @file   chaos.h
/// @author __Roselle__
/// @date   2026-02-20
/// @brief  A module that computes a chaotic permutation based on various
///         chaotic maps and an initial seed.
#include <vector>
#include <functional>

/// @brief  Computes the value of the tent map at a given point.
/// @param  x   the input value, typically in the range [0, 1] (double)
/// @param  mu  the parameter of the tent map, default is 2.0 (double)
/// @return the output value of the tent map (double)
double tent_map(double x, double mu = 2.0);

/// @brief  Generates a chaotic permutation of integers from 0 to n-1 based on
///         the a chaotic map and an initial seed.
/// @param  n       the size of the permutation (int)
/// @param  seed    the initial seed for the chaotic map (double)
/// @param  map_func the chaotic map to be used (std::function<double(double)>)
/// @return a vector of integers representing the chaotic permutation, where
std::vector<int> generate_chaotic_permutation(
    int n, double seed, std::function<double(double)> map
);