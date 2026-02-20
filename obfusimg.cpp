/// @file   obfusimg.cpp
/// @author __Roselle__, Hannah
/// @date   2024-06
/// @brief  Example test cases for the obfusimg module that obfuscates images
///         by shuffling the pixels of the image in a deterministic way.
#include <string>
#include <print>
using std::string;
using std::println;

/// @brief  The main function takes 3 arguments,
///         - image path (std::string)
///         - obfusication algorithm (int)
///         - obfusication seed (float)
int main(int argc, char* argv[]){
    // Handle TUI arguments
    string img_path = argv[1];
    int obfus_alg = std::stoi(argv[2]);
    double obfus_seed = std::stoi(argv[3]);
    println("my path is {}", img_path);
    return 0;
}