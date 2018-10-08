#pragma once

namespace rayray
{
    class view_plane
    {
        int horizontal_resolution_{ 1 };
        int vertical_resolution_{ 1 };
        float pixel_size_{ 1.0 };
        float gamma_{ 1.0 };
        float inverse_gamma_{ 1.0 };

    public:
        view_plane(const int &h_res, const int &v_res, const float &pixel_size, const float &gamma);
        int horizontal_resolution() const;
        void set_horizontal_resolution(const int horizontal_resolution);
        int vertical_resolution() const;
        void set_vertical_resolution(const int vertical_resolution);
        float pixel_size() const;
        void set_pixel_size(const float pixel_size);
        float gamma() const;
        void set_gamma(const float gamma);
        float inverse_gamma() const;
        void set_inverse_gamma(const float inverse_gamma);
    };
}