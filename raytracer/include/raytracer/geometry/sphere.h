#pragma once
#include "geometric_object.h"

namespace rayray
{
	class sphere : public geometric_object
	{
	public:
		sphere(const point<double, 3> &center, const double &radius);
        bool hit(const rayray::ray& ray, double& t_min, rayray::shade_rec& sr) const override;

	    point<double, 3> center() const;
	    void set_center(const point<double, 3>& center);
	    double radius() const;
	    void set_radius(const double radius);
	private:
		point<double, 3> center_;
		double radius_;
		static const double k_epsilon;
	};
}
