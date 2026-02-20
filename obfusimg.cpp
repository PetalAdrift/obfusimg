/// @file   obfusimg.cpp
/// @author __roselle__, pigeon.hannah
/// @date   2026-02-20
/// @brief  An application that obfuscates images by shuffling the pixels of the
///         image in a deterministic and invertible way.
#include <string>
#include <iostream>
#include <cmath>
#include "stb_image.h"
#include "stb_image_write.h"
#include "permutation.h"
#include "gilbert_curve.h"
#include "chaos.h"
using std::string;

/// @brief  The main function takes 3 TUI arguments,
///         - image path (std::string)
///         - obfusication algorithm (int)
///         - obfusication seed (float)
int main(int argc, char* argv[]){
    // handle TUI arguments
    string img_path = argv[1];
    int obfus_alg = std::stoi(argv[2]);
    double obfus_seed = std::stod(argv[3]);
    
    // verify file extension
    size_t dot = img_path.find_last_of('.');
    std::string ext = img_path.substr(dot + 1);
    if (ext != "png" && ext != "jpg" && ext != "jpeg") {
        std::cerr << "Unsupported format\n";
        return 1;
    }

    // image input
    int width, height, channels;
    unsigned char *pixels = stbi_load(
        // read image as is, without forcing a specific number of channels (0)
        img_path.c_str(), &width, &height, &channels, 0
    );
    
    unsigned char* new_pixels = nullptr;
    // compute golden ratio-based offset for shift
    int offset = std::round((std::sqrt(5.0) - 1.0) / 2.0 * width * height);

    switch(obfus_alg){
        case 0:{
        // compact index gilbert curve obfuscation
        std::vector<int> g_func = generate_compact_g_function(width, height);
        g_func = normalize_permutation(g_func);
        g_func = shift_sequence(g_func, offset);
        new_pixels = apply_permutation(
            pixels, g_func, width, height, channels
        );
        break;
        }

        case 1:{
        // invert compact index gilbert curve obfuscation
        std::vector<int> g_func = generate_compact_g_function(width, height);
        g_func = normalize_permutation(g_func);
        g_func = shift_sequence(g_func, offset);
        std::vector<int> inv_g_func = invert_permutation(g_func);
        new_pixels = apply_permutation(
            pixels, inv_g_func, width, height, channels
        );
        break;
        }

        case 2:{
        // exact gilbert curve obfuscation
        std::vector<int> g_func = generate_exact_g_function(width, height);
        g_func = shift_sequence(g_func, offset);
        new_pixels = apply_permutation(
            pixels, g_func, width, height, channels
        );
        break;
        }

        case 3:{
        // invert exact gilbert curve obfuscation
        std::vector<int> g_func = generate_exact_g_function(width, height);
        g_func = shift_sequence(g_func, offset);
        std::vector<int> inv_g_func = invert_permutation(g_func);
        new_pixels = apply_permutation(
            pixels, inv_g_func, width, height, channels
        );
        break;
        }

        case 4:{
        // chaos (tent map) obfuscation
        std::vector<int> chaotic_perm = generate_chaotic_permutation(
            width * height, obfus_seed, 
            [](double x){return tent_map(x, 1.9999);}  // use mu \approx 2
        );
        new_pixels = apply_permutation(
            pixels, chaotic_perm, width, height, channels
        );
        break;
        }

        case 5:{
        // invert chaos (tent map) obfuscation
        std::vector<int> chaotic_perm = generate_chaotic_permutation(
            width * height, obfus_seed, 
            [](double x){return tent_map(x, 1.9999);}
        );
        std::vector<int> inv_chaotic_perm = invert_permutation(chaotic_perm);
        new_pixels = apply_permutation(
            pixels, inv_chaotic_perm, width, height, channels
        );
        }
    }

    if (new_pixels == nullptr) {
        std::cerr << "Error: No obfuscation algorithm was applied.\n";
        stbi_image_free(pixels);
        return 2;
    }
          
    // free memory
    stbi_image_free(pixels);
    
    // image output
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
    }

    if (!ok) {
        std::cerr << "Failed to write image\n";
        delete[] new_pixels;
        return 3;
    }

    // free memory
    delete[] new_pixels;
    return 0;
}