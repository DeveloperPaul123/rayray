#pragma once
#include <vector>
#include "raytracer/geometry/geometric_object.h"
#include "rgb_color.h"
#include "raytracer/geometry/sphere.h"
#include "view_plane.h"
#include <memory>
#include "raytracer/image/image.h"
#include "raytracer/lights/ambient_light.h"

namespace rayray
{
	class tracer;

	class scene
	{
	public:
		scene();
        virtual ~scene();
        void set_tracer(tracer *t);
        tracer* tracer_ptr() const;
        void set_ambient_light(ambient_light* light);
        ambient_light* ambient_light_ptr() const;
        void add_object(rayray::geometric_object* object);
        std::vector<rayray::geometric_object*> objects() const;

        void add_light(light* light);
        void set_lights(const std::vector<light*> &lights);
        std::vector<light*> lights() const;
	    const view_plane& view_plane() const;
	    void set_view_plane(const rayray::view_plane& view_plane);
	    const rgb_color& background_color() const;
	    void set_background_color(const rgb_color& background_color);

        shade_rec hit_objects(const ray &ray);
	private:
        rayray::view_plane view_plane_;
		rgb_color background_color_;
		std::vector<rayray::geometric_object*> hit_objects_;
        std::vector<rayray::light*> lights_;
        tracer *tracer_{ nullptr };
        ambient_light *ambient_ptr_{nullptr};
	};
}
