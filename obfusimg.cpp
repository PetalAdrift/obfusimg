/// @file   obfusimg.cpp
/// @author __Roselle__
/// @date   2026-02-19
/// @brief  An application that obfuscates images by shuffling the pixels of the
///         image in a deterministic and invertible way.
#include <string>
#include <print>
#include <iostream>
#include "gilbert_curve.h"
#include "stb_image.h"
#include "stb_image_write.h"
using std::string;
using std::println;

/// @brief  Function to normalize a given permutation by associating each 
///         element with its rank in the permutation.
/// @param  perm    the permutation to be normalized (std::vector<int>)
/// @return the normalized permutation (std::vector<int>)
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

/// @brief  Function to invert a given permutation.
/// @param  perm    the permutation to be inverted (std::vector<int>) 
/// @return the inverted permutation (std::vector<int>)
std::vector<int> invert_permutation(const std::vector<int>& perm){
    std::vector<int> inv_perm(perm.size());
    for (size_t i = 0; i < perm.size(); i++) {
        inv_perm[perm[i]] = i;
    }
    return inv_perm;
}

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
){
    size_t total = width * height * channels;  // size of pixels array
    unsigned char* new_pixels = new unsigned char[total];
    for (size_t i = 0; i < width * height; i++) {
        for (int c = 0; c < channels; c++) {
            new_pixels[i * channels + c] = pixels[perm[i] * channels + c];
        }
    }
    return new_pixels;
}

/// @brief  The main function takes 3 TUI arguments,
///         - image path (std::string)
///         - obfusication algorithm (int)
///         - obfusication seed (float)
int main(int argc, char* argv[]){
    // handle TUI arguments
    string img_path = argv[1];
    int obfus_alg = std::stoi(argv[2]);
    double obfus_seed = std::stoi(argv[3]);

    // image input
    int width, height, channels;
    unsigned char *pixels = stbi_load(
        // read image as is, without forcing a specific number of channels (0)
        img_path.c_str(), &width, &height, &channels, 0
    );
    size_t total = (size_t)width * height * channels;  // size of pixels array
    
    unsigned char* new_pixels;

    auto g = generate_g_function(width, height);
    g = normalize_permutation(g);
    const int N = width * height;
    if ((int)g.size() != N) {
        std::cerr << "g_func size mismatch: " << g.size() << " vs " << N << "\n";
        return 1;
    }
    for (int i = 0; i < N; ++i) {
        if (g[i] < 0 || g[i] >= N) {
            std::cerr << "g_func out of range at i=" << i << ": " << g[i] << "\n";
            return 1;
        }
    }

    switch(obfus_alg){
        case 0:{
        // gilbert curve obfuscation
        std::vector<int> g_func = generate_g_function(width, height);
        g_func = normalize_permutation(g_func);
        new_pixels = apply_permutation(
            pixels, g_func, width, height, channels
        );
        break;
        }

        case 1:{
        // invert gilbert curve obfuscation
        std::vector<int> g_func = generate_g_function(width, height);
        g_func = normalize_permutation(g_func);
        std::vector<int> inv_g_func = invert_permutation(g_func);
        new_pixels = apply_permutation(
            pixels, inv_g_func, width, height, channels
        );
        break;
        }

        case 2:
        // chaotic system permutation
        break;

        case 3:
        // invert chaotic system permutation
        break;
    }
          
    // free memory
    stbi_image_free(pixels);

    
    size_t dot = img_path.find_last_of('.');
    std::string ext = img_path.substr(dot + 1);
    std::string out_name = img_path.substr(0, dot) + "_out." + ext;

    bool ok = false;
    if (ext == "png") {
        ok = stbi_write_png(
            out_name.c_str(), width, height, channels, new_pixels, width * channels
        );
    } else if (ext == "jpg" || ext == "jpeg") {
        ok = stbi_write_jpg(
            out_name.c_str(), width, height, channels, new_pixels, 95
        );
    } else {
        std::cerr << "Unsupported format\n";
    }
    
    return 0;
}