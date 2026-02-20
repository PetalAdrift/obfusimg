/// @file   gilbert_curve.h
/// @author __roselle__, pigeon.hannah
/// @date   2026-02-20
/// @brief  A module that computes a generalized hilbert curve for an arbitrary
///         2-dimensional rectangle.
#include <vector>

/// @brief  Function to compute the nth bit of an integer in binary.
/// @param  val the interger to be represented in binary (int)
/// @param  bit the position of the bit to be extracted, 
///         where 0 is the least significant bit (int)  
/// @return the value of the nth bit (0 or 1) (int)
int get_bit(int val, int bit);

/// @brief  Function to compute the sign of an integer.
/// @param  x   the integer whose sign is to be computed (int)
/// @return 1 if x is positive, -1 if x is negative, and 0 if x is zero (int)
int sign(int x);

/// @brief  Function to perform floor division by 2 for integers.
/// @param  x   the integer to be divided (int)
/// @return the result of floor division of x by 2 (int)
int floor_div2(int x);

/// @brief  Function to compute the Compact Hilbert Index for a 2D point.
///         The index can be imagined as the position of the point along a
///         Gilbert curve that fills the smallest containing rectangle of size
///         2^w_prec by 2^h_prec.
/// @param  x       the horizontal coordinate of the point (int)
/// @param  y       the vertical coordinate of the point (int)
/// @param  w_prec  the precision (number of bits) needed to represent the 
///                 width of the rectangle (int)
/// @param  h_prec  the precision (number of bits) needed to represent the 
///                 height of the rectangle (int)
/// @return the Compact Hilbert Index corresponding to the point (int)
/// @cite   https://doi.org/10.1016/j.ipl.2007.08.034
int get_compact_index(int x, int y, int w_prec, int h_prec);

/// @brief  Function to compute the compact g function for a given rectangle.
///         This g function needs to be normalized.
/// @param  w   the width of the rectangle (int)
/// @param  h   the height of the rectangle (int)
/// @return a vector of integers representing the $g$ function, where the value 
///         at index $i$ is the Compact Hilbert Index of the point corresponding 
///         to the original index $i$ in row-major order (std::vector<int>)
std::vector<int> generate_compact_g_function(int w, int h);

/// @brief  Recursive function to compute the coordinates of the points along an
///         exact Gilbert curve by dividing the rectangle into smaller blocks.
/// @param  x           the starting absolute horizontal coordinate of the 
///                     current block (int)
/// @param  y           the starting absolute vertical coordinate of the 
///                     current block (int)
/// @param  ax          the width of the major axis of the current block with 
///                     signature indicating movement direction (int)
/// @param  ay          the height of the major axis of the current block with
///                     signature indicating movement direction (int)
/// @param  bx          the width of the minor axis of current block with 
///                     signature indicating movement direction (int)
/// @param  by          the height of the minor axis of current block with
///                     signature indicating movement direction (int)
/// @param  img_width   the total width of the image, used to compute 1D indices
///                     from 2D coordinates (int)
/// @param  coordinates reference to the output vector (std::vector<int>)
void draw_gilbert_curve(
    int x, int y, int ax, int ay, int bx, int by, int img_width, 
    std::vector<int>& coordinates
);

/// @brief  Function to compute the exact g function for a given rectangle.
///         This g function is normalized.
/// @param  w   the width of the rectangle (int)
/// @param  h   the height of the rectangle (int)
/// @return a vector of integers representing the $g$ function, where the value 
///         at index $i$ is the Compact Hilbert Index of the point corresponding 
///         to the original index $i$ in row-major order (std::vector<int>)
std::vector<int> generate_exact_g_function(int width, int height);