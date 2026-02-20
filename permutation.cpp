/// @file   permutation.cpp
/// @author __roselle__, pigeon.hannah
/// @date   2026-02-20
/// @brief  A module that handles permutations encoded as vectors of integers.
#include <algorithm>
#include "permutation.h"

std::vector<int> normalize_permutation(const std::vector<int>& perm) {
    int n = perm.size();

    // pair each value with its original index
    std::vector<std::pair<int,int>> indexed(n);
    for (int i = 0; i < n; ++i) {
        indexed[i] = {perm[i], i};
    }

    // stable sort by value
    std::stable_sort(indexed.begin(), indexed.end(),
        [](const auto& a, const auto& b) {
            return a.first < b.first;
        });

    // assign ranks
    std::vector<int> normalized(n);
    for (int rank = 0; rank < n; ++rank) {
        int original_index = indexed[rank].second;
        normalized[original_index] = rank;
    }

    return normalized;
}

std::vector<int> shift_sequence(const std::vector<int>& seq, int shift) {
    int n = seq.size();
    std::vector<int> shifted(n);
    for (int i = 0; i < n; ++i) {
        shifted[seq[(i + shift) % n]] = seq[i];  // forward shift
    }
    return shifted;
}

std::vector<int> invert_permutation(const std::vector<int>& perm){
    std::vector<int> inv_perm(perm.size());
    for (size_t i = 0; i < perm.size(); i++) {
        inv_perm[perm[i]] = i;
    }
    return inv_perm;
}

unsigned char* apply_permutation(
    unsigned char* pixels, std::vector<int> perm, 
    int width, int height, int channels
){
    size_t total = width * height * channels;  // size of pixels array
    unsigned char* new_pixels = new unsigned char[total];
    for (size_t i = 0; i < (size_t)width * height; i++) {
        for (int c = 0; c < channels; c++) {
            new_pixels[i * channels + c] = pixels[perm[i] * channels + c];
        }
    }
    return new_pixels;
}