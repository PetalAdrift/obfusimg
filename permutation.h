/// @file   permutation.h
/// @author __roselle__, pigeon.hannah
/// @date   2026-02-20
/// @brief  A module that handles permutations encoded as vectors of integers.
#include <vector>

/// @brief  Function to normalize a given permutation by associating each 
///         element with its rank in the permutation.
/// @param  perm    the permutation to be normalized (std::vector<int>)
/// @return the normalized permutation (std::vector<int>)
std::vector<int> normalize_permutation(const std::vector<int>& perm);

/// @brief  Function that computes a permutation by shifting a sequence a(n)
///         such that a(n) lands in the position of a(n + shift).
/// @param  seq     the original sequence to be shifted (std::vector<int>)
/// @param  shift   the number of positions to shift the sequence (int)
/// @return the shifted sequence as a permutation (std::vector<int>)
std::vector<int> shift_sequence(const std::vector<int>& seq, int shift);

/// @brief  Function to invert a given permutation.
/// @param  perm    the permutation to be inverted (std::vector<int>) 
/// @return the inverted permutation (std::vector<int>)
std::vector<int> invert_permutation(const std::vector<int>& perm);

/// @brief  Function to apply a permutation to an image's pixel data.
/// @param  pixels      the pixel data of the original image (unsigned char*)
/// @param  perm        the permutation to be applied to the pixel data 
///                     (std::vector<int>)
/// @param  width       the width of the image (int)
/// @param  height      the height of the image (int)
/// @param  channels    the number of channels in the image (int)
/// @return the obfuscated pixel data (unsigned char*)
unsigned char* apply_permutation(
    unsigned char* pixels, std::vector<int> perm, 
    int width, int height, int channels
);