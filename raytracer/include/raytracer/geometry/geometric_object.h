#pragma once
#include "raytracer/core/ray.h"
#include "raytracer/core/rgb_color.h"
#include "raytracer/materials/material.h"

namespace rayray
{
	class shade_rec;

	class geometric_object
	{
        rgb_color color_;
        material *material_ptr_;
	public:
		geometric_object() = default;
		virtual ~geometric_object() = default;
		virtual bool hit(const rayray::ray & ray, double &t_min, rayray::shade_rec &sr) const = 0;
        virtual const rgb_color& color() const;
        virtual void set_color(const rgb_color& color);
        virtual void set_material(material* mat);
        virtual material* material_ptr() const;
	};

    inline const rgb_color& geometric_object::color() const
    {
        return color_;
    }

    inline void geometric_object::set_color(const rgb_color& color)
    {
        color_ = color;
    }

    inline void geometric_object::set_material(material* mat)
    {
        material_ptr_ = mat;
    }

    inline material* geometric_object::material_ptr() const
    {
        return material_ptr_;
    }

}
