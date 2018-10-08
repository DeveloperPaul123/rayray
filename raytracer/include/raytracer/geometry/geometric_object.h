#pragma once
#include "raytracer/core/ray.h"
#include "raytracer/core/rgb_color.h"

namespace rayray
{
	class shade_rec;

	class geometric_object
	{
        rgb_color color_;
	public:
		geometric_object() = default;
		virtual ~geometric_object() = default;
		virtual bool hit(const rayray::ray & ray, double &t_min, rayray::shade_rec &sr) const = 0;
        virtual const rgb_color& color() const;
        virtual void set_color(const rgb_color& color);
	};

    inline const rgb_color& geometric_object::color() const
    {
        return color_;
    }

    inline void geometric_object::set_color(const rgb_color& color)
    {
        color_ = color;
    }

}
