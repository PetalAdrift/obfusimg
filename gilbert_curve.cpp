/// @file   gilbert_curve.cpp
/// @author __roselle__, pigeon.hannah
/// @date   2026-02-20
/// @brief  A module that computes a generalized hilbert curve for an arbitrary
///         2-dimensional rectangle.
#include <algorithm>
#include <cmath>
#include "gilbert_curve.h"

int get_bit(int val, int bit) {
    return (val >> bit) & 1;
}

int sign(int x) {
    return (x > 0) - (x < 0);
}

int floor_div2(int x) {
    return x >= 0 ? x / 2 : (x - 1) / 2;
}

// this function is adapted from the original algorithm in the paper,
// it is heavily modified by an LLM with C-style coding conventions
int get_compact_index(int x, int y, int w_prec, int h_prec) {
    // maximum number of bits needed to represent either dimension
    int max_prec = std::max(w_prec, h_prec);
    // the resulting compact index
    int h_c = 0;
    // e tracks flips (reflections), d tracks swaps (diagonal rotations)
    int e = 0, d = 0;

    for (int i = max_prec - 1; i >= 0; --i) { 
        // identify active dimensions at this bit level
        bool x_active = (w_prec > i);
        bool y_active = (h_prec > i);

        // extract bits for active dimensions, treating inactive as 0
        int bx = x_active ? get_bit(x, i) : 0;
        int by = y_active ? get_bit(y, i) : 0;

        // compute the 2-bit quadrant code l (from 0 to 3) for the current level
        int l = (bx << 1) | by; 
        
        // apply axis swap if direction d indicates a rotation
        int l_swapped = d ? ((l >> 1) | ((l & 1) << 1)) : l;
        
        // compute the normalized position t based on flip mask e and swapped l
        int t = l_swapped ^ e; 
        
        // calculate rank (position in quadrant considering active dimensions)
        int bits_to_add = (x_active ? 1 : 0) + (y_active ? 1 : 0); 
        int r = 0;
        
        // GRAYCODERANK 
        if (x_active && y_active) {
            // True Inverse Gray Code maps t (0-3) safely to rank r (0-3)
            r = (t == 0) ? 0 : (t == 1) ? 1 : (t == 3) ? 2 : 3;
            
            // update entry e and direction d for recursion ONLY in 2D space
            if (r == 0) {
                d ^= 1; // swap axes
            } else if (r == 3) {
                d ^= 1; // swap axes
                e ^= 3; // flip both axes (binary 11)
            }
        } else {
            // only one dimension is active, take its bit
            if (x_active) {
                r = (t >> (d ? 0 : 1)) & 1;
            } else {
                r = (t >> (d ? 1 : 0)) & 1;
            }
        }

        // append rank to index for next bit level 
        h_c = (h_c << bits_to_add) | r;
    }
    return h_c;
}

std::vector<int> generate_compact_g_function(int w, int h) {
    int w_prec = std::ceil(std::log2(w)); // Bits needed for Width 
    int h_prec = std::ceil(std::log2(h)); // Bits needed for Height 
    
    std::vector<int> gc(h * w);

    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            // Store the 1D Hilbert address for each 2D pixel
            gc[r * w + c] = get_compact_index(c, r, w_prec, h_prec);
        }
    }
    return gc;
}

void draw_gilbert_curve(
    int x, int y, int ax, int ay, int bx, int by, int img_width, 
    std::vector<int>& coordinates
) {
    int w = std::abs(ax + ay);
    int h = std::abs(bx + by);

    int dax = sign(ax), day = sign(ay);
    int dbx = sign(bx), dby = sign(by);

    if (h == 1) {
        // trivial row fill
        for (int i = 0; i < w; ++i) {
            coordinates.push_back(y * img_width + x);
            x += dax;
            y += day;
        }
        return;
    }

    if (w == 1) {
        // trivial column fill
        for (int i = 0; i < h; ++i) {
            coordinates.push_back(y * img_width + x);
            x += dbx;
            y += dby;
        }
        return;
    }

    int ax2 = floor_div2(ax), ay2 = floor_div2(ay);
    int bx2 = floor_div2(bx), by2 = floor_div2(by);

    int w2 = std::abs(ax2 + ay2);
    int h2 = std::abs(bx2 + by2);

    if (2 * w > 3 * h) {
        if ((w2 % 2 != 0) && (w > 2)) {
            // prefer even steps
            ax2 += dax;
            ay2 += day;
        }

        // long case: split in two parts only
        draw_gilbert_curve(
            x, y, ax2, ay2, bx, by, img_width, coordinates
        );
        draw_gilbert_curve(
            x + ax2, y + ay2, ax - ax2, ay - ay2, bx, by, img_width, coordinates
        );

    } else {
        if ((h2 % 2 != 0) && (h > 2)) {
            // Prefer even steps
            bx2 += dbx;
            by2 += dby;
        }

        // standard case: one step up, one long horizontal, one step down
        draw_gilbert_curve(
            x, y, bx2, by2, ax2, ay2, img_width, coordinates
        );
        draw_gilbert_curve(
            x + bx2, y + by2, ax, ay, bx - bx2, by - by2, img_width, coordinates
        );
        draw_gilbert_curve(
            x + (ax - dax) + (bx2 - dbx), y + (ay - day) + (by2 - dby), 
            -bx2, -by2, -(ax - ax2), -(ay - ay2), img_width, coordinates
        );
    }
}

std::vector<int> generate_exact_g_function(int width, int height) {
    std::vector<int> coordinates;
    coordinates.reserve(width * height);

    if (width >= height) {
        draw_gilbert_curve(0, 0, width, 0, 0, height, width, coordinates);
    } else {
        draw_gilbert_curve(0, 0, 0, height, width, 0, width, coordinates);
    }

    return coordinates;
}