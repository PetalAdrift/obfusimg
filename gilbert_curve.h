/// @file   gilbert_curve.h
/// @author __Roselle__
/// @date   2026-02-19
/// @brief  A module that computes a generalized hilbert curve for an arbitrary
///         2-dimensional rectangle.
#include <vector>

/// @brief  Function to compute the nth bit of an integer in binary.
/// @param  val the interger to be represented in binary (int)
/// @param  bit the position of the bit to be extracted, 
///         where 0 is the least significant bit (int)  
/// @return the value of the nth bit (0 or 1) (int)
inline int get_bit(int val, int bit);

/// @brief  Function to compute the Compact Hilbert Index for a 2D point.
/// @param  x       the horizontal coordinate of the point (int)
/// @param  y       the vertical coordinate of the point (int)
/// @param  w_prec  the precision (number of bits) needed to represent the 
///                 width of the rectangle (int)
/// @param  h_prec  the precision (number of bits) needed to represent the 
///                 height of the rectangle (int)
/// @return the Compact Hilbert Index corresponding to the point (int)
/// @cite   https://doi.org/10.1016/j.ipl.2007.08.034
int get_compact_index(int x, int y, int w_prec, int h_prec);

/// @brief  Function to generate the $g$ function for a given rectangle size.
/// @param  w   the width of the rectangle (int)
/// @param  h   the height of the rectangle (int)
/// @return a vector of integers representing the $g$ function, where the value 
///         at index $i$ is the Compact Hilbert Index of the point corresponding 
///         to the original index $i$ in row-major order (std::vector<int>)
std::vector<int> generate_g_function(int w, int h);