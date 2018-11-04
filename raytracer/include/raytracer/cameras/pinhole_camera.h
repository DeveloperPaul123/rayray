#pragma once
#include "camera.h"

namespace rayray
{
    class pinhole_camera : public camera
    {
    public:
        pinhole_camera();
        image<unsigned char> render_scene(const scene &scene) override;
        void set_zoom(const double &z);
        double zoom() const;
        void set_view_plane_distance(const double &d);
        double view_plane_distance() const;
    private:
        vector<double, 3> get_direction(const point<double> &point);
        double d_;
        double zoom_;
    };
}
