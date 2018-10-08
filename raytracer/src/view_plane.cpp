#include "raytracer/core/view_plane.h"

rayray::view_plane::view_plane(const int& h_res, const int& v_res, const float& pixel_size, const float& gamma)
    : horizontal_resolution_(h_res), vertical_resolution_(v_res), pixel_size_(pixel_size), 
        gamma_(gamma), inverse_gamma_(1.0f / gamma)
{
}

int rayray::view_plane::horizontal_resolution() const
{
    return horizontal_resolution_;
}

void rayray::view_plane::set_horizontal_resolution(int horizontal_resolution)
{
    horizontal_resolution_ = horizontal_resolution;
}

int rayray::view_plane::vertical_resolution() const
{
    return vertical_resolution_;
}

void rayray::view_plane::set_vertical_resolution(int vertical_resolution)
{
    vertical_resolution_ = vertical_resolution;
}

float rayray::view_plane::pixel_size() const
{
    return pixel_size_;
}

void rayray::view_plane::set_pixel_size(float pixel_size)
{
    pixel_size_ = pixel_size;
}

float rayray::view_plane::gamma() const
{
    return gamma_;
}

void rayray::view_plane::set_gamma(float gamma)
{
    gamma_ = gamma;
}

float rayray::view_plane::inverse_gamma() const
{
    return inverse_gamma_;
}

void rayray::view_plane::set_inverse_gamma(float inverse_gamma)
{
    inverse_gamma_ = inverse_gamma;
}
