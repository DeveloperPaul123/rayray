#pragma once
#include "geometric_object.h"

namespace rayray
{
	class plane : public geometric_object
	{
	public:

		plane(const point<double, 3> &point, const vector<double, 3> &normal);
		bool hit(const rayray::ray& ray, double& t_min, rayray::shade_rec& sr) const override;

	private:
		point<double, 3> point_;
		vector<double, 3> normal_;
		static const double k_epsilon;
	};
}
