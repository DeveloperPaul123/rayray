#pragma once
#include "raytracer/core/vector.h"

namespace rayray
{
	class ray
	{
	public:
		using scalar = double;
		using vec3 = vector<scalar, 3>;
		ray() = default;
		ray(const vec3 &origin, const vec3 & direction);
		~ray() = default;

        void set_direction(const vec3 &dir);
        void set_origin(const vec3 &origin);
		vec3 origin() const;
		vec3 direction() const;
	private:
		vec3 origin_;
		vec3 direction_;
	};
}
