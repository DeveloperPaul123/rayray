#include "raytracer/cameras/camera.h"

rayray::camera::camera()
    : eye_{0, 0, 500}, lookat_(0, 0, 0), roll_angle_(0), 
        u({ 1.0, 0.0, 0.0 }), v({ 0, 1, 0 }), w({ 0, 0, 1 }), 
        up({ 0.0, 1.0, 0.0 }), exposure_time(1.0)
{
    
}

rayray::camera::~camera()
{
}

void rayray::camera::set_eye(const double x, const double y, const double z)
{
    eye_ = { x, y, z };
}

void rayray::camera::set_lookat(const point<double, 3>& p)
{
    lookat_ = p;
}

void rayray::camera::set_lookat(const double x, const double y, const double z)
{
    lookat_ = { x, y, z };
}

void rayray::camera::set_up_vector(const vector<double, 3>& u)
{
    up = u;
}

void rayray::camera::set_up_vector(const double x, const double y, const double z)
{
    up = { x, y, z };
}

void rayray::camera::set_roll(const double ra)
{
    roll_angle_ = ra;
}

void rayray::camera::set_exposure_time(const double exposure)
{
    exposure_time = exposure;
}

void rayray::camera::set_eye(const point<double, 3>& p)
{
    eye_ = p;
}

void rayray::camera::compute_uvw()
{
    // construct the orthonormal basis for the camera. 
    // note that the origina of the ONB is the eye_
    auto w_temp = eye_ - lookat_;
    auto w_unnormalized = vector<double, 3>({ w_temp[0], w_temp[1], w_temp[2] });
    // w points in the opposite direction of (lookat - eye)
    w = w_unnormalized.to_unit_vector();
    auto cross_result = cross(up, w);
    // u is perpendicular to w, but in the same plane
    u = cross_result.to_unit_vector();
    // v is perpendicular to w and u
    v = cross(w, u);

    // take care of the singularity by hardwiring in specific camera orientations
    // camera looking vertically down
    if (eye_.x() == lookat_.x() && eye_.z() == lookat_.z() && eye_.y() > lookat_.y()) { 
        u = vector<double, 3>({ 0, 0, 1 });
        v = vector<double, 3>({1, 0, 0});
        w = vector<double, 3>({ 0, 1, 0 });
    }
    // camera looking vertically up
    if (eye_.x() == lookat_.x() && eye_.z() == lookat_.z() && eye_.y() < lookat_.y()) { 
        u = vector<double, 3>({ 1, 0, 0 });
        v = vector<double, 3>({ 0, 0, 1 });
        w = vector<double, 3>({ 0, -1, 0 });
    }
}
