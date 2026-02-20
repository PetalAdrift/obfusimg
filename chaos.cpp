/// @file   chaos.cpp
/// @author __Roselle__, pigeon.hannah
/// @date   2026-02-20
/// @brief  A module that computes a chaotic permutation based on various
///         chaotic maps and an initial seed.
#include <cmath>
#include <algorithm>
#include "chaos.h"

double tent_map(double x, double mu){
    if (x < 0.5) {
        return mu * x;
    } else {
        return mu * (1.0 - x);
    }
}

std::vector<int> generate_chaotic_permutation(
    int n, double seed, std::function<double(double)> map
){
    std::vector<std::pair<double, int>> chaotic_values(n);
    double x = seed - std::floor(seed);  // ensure seed is in [0, 1)
    for (int i = 0; i < n; ++i) {
        x = map(x);
        chaotic_values[i] = {x, i};  // include original index for bookkeeping
    }
    std::sort(chaotic_values.begin(), chaotic_values.end());
    std::vector<int> perm(n);
    for (int i = 0; i < n; ++i) {
        perm[i] = chaotic_values[i].second;  // extract original index
    }
    return perm;
}