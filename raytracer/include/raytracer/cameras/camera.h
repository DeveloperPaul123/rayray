#pragma once

#include "raytracer/core/point.h"
#include "raytracer/core/vector.h"
#include "raytracer/core/scene.h"

namespace rayray
{
    class camera
    {
    public:
        camera();   							// default constructor
        virtual ~camera();

        virtual image<unsigned char> render_scene(const scene& w) = 0;
        void set_eye(const point<double, 3>& p);
        void set_eye(const double x, const double y, const double z);
        void set_lookat(const point<double, 3>& p);
        void set_lookat(const double x, const double y, const double z);
        void set_up_vector(const vector<double, 3>& u);
        void set_up_vector(const double x, const double y, const double z);
        void set_roll(const double ra);
        void set_exposure_time(const double exposure);

        void compute_uvw(void);


    protected:
        point<double, 3> eye_;				// eye point
        point<double, 3> lookat_; 			// lookat point
        double roll_angle_;					// roll angle
        vector<double, 3> u;
        vector<double, 3> v; 
        vector<double, 3> w;			// orthonormal basis vectors
        vector<double, 3> up;					// up vector
        double exposure_time;
    };
}