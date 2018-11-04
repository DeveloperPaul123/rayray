
cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

project(raytracer)

set(project_core_headers
    include/raytracer/core/nd_base.h
    include/raytracer/core/point.h
    include/raytracer/core/vector.h 
    include/raytracer/core/ray.h
    include/raytracer/core/scene.h
    include/raytracer/core/shade_rec.h
    include/raytracer/core/rgb_color.h
    include/raytracer/core/view_plane.h
    include/raytracer/core/scene_renderer.h
)

set(project_image_headers
    include/raytracer/image/image.h
    include/raytracer/image/image_io.h
)

set(project_geometry_headers
    include/raytracer/geometry/geometric_object.h
    include/raytracer/geometry/sphere.h
    include/raytracer/geometry/plane.h
)

set(project_tracer_headers
    include/raytracer/tracers/tracer.h
    include/raytracer/tracers/single_sphere_tracer.h
    include/raytracer/tracers/multi_object_tracer.h
)

set(project_samplers_headers
    include/raytracer/samplers/sampler.h
    include/raytracer/samplers/regular_sampler.h
    include/raytracer/samplers/jittered_sampler.h
    include/raytracer/samplers/pure_random_sampler.h
    include/raytracer/samplers/multijittered_sampler.h
    include/raytracer/samplers/nrooks_sampler.h
    include/raytracer/samplers/hammersley_sampler.h
)

set(project_camera_headers
    include/raytracer/cameras/camera.h
    include/raytracer/cameras/pinhole_camera.h)

set(project_utilities_headers
    include/raytracer/utilities/math.h
    include/raytracer/utilities/constants.h
)

set(project_brdf_headers
    include/raytracer/brdf/brdf.h
    include/raytracer/brdf/lambertian.h
)

set(project_headers
    ${project_core_headers}
    ${project_image_headers}
    ${project_geometry_headers}
    ${project_tracer_headers}
    ${project_samplers_headers}
    ${project_camera_headers}
    ${project_utilities_headers}
    ${project_brdf_headers}
    )

set(project_core_sources
    src/image_io.cpp
    src/ray.cpp
    src/view_plane.cpp
    src/scene.cpp
    src/shade_rec.cpp
    src/rgb_color.cpp
    src/scene_renderer.cpp
)

set(project_geometry_sources
    src/sphere.cpp
    src/plane.cpp
)

set(project_tracer_sources
    src/tracer.cpp
    src/single_sphere_tracer.cpp
    src/multi_object_tracer.cpp
)

set(project_sampler_sources
    src/sampler.cpp
    src/jittered_sampler.cpp
    src/pure_random_sampler.cpp
    src/regular_sampler.cpp
    src/nrooks_sampler.cpp
    src/hammersley_sampler.cpp
    src/multijittered_sampler.cpp
)

set(project_utilities_sources
    src/math.cpp
)

set(project_camera_sources
    src/camera.cpp
    src/pinhole_camera.cpp
)

set(project_brdf_sources
    src/lambertian.cpp)

set(project_sources
    ${project_core_sources}     
    ${project_geometry_sources}
    ${project_tracer_sources}
    ${project_sampler_sources}
    ${project_utilities_sources}   
    ${project_camera_sources}
    ${project_brdf_sources}
)

source_group("Header Files\\Core" FILES ${project_core_headers})
source_group("Header Files\\Image" FILES ${project_image_headers})
source_group("Header Files\\Geometry" FILES ${project_geometry_headers})
source_group("Header Files\\Tracer" FILES ${project_tracer_headers})
source_group("Header Files\\Samplers" FILES ${project_samplers_headers})
source_group("Header Files\\Utilities" FILES ${project_utilities_headers})
source_group("Header Files\\Cameras" FILES ${project_camera_headers})
source_group("Header Files\\BRDF" FILES ${project_brdf_headers})

source_group("Source Files\\Core" FILES ${project_core_sources})
source_group("Source Files\\Geometry" FILES ${project_geometry_sources})
source_group("Source Files\\Tracer" FILES ${project_tracer_sources})
source_group("Source Files\\Samplers" FILES ${project_sampler_sources})
source_group("Source Files\\Utilities" FILES ${project_utilities_sources})
source_group("Source Files\\Cameras" FILES ${project_camera_sources})
source_group("Source Files\\BRDF" FILES ${project_brdf_sources})

add_library(${PROJECT_NAME} ${project_headers} ${project_sources})

target_include_directories(${PROJECT_NAME} PUBLIC include)

if(RAYRAY_BUILD_TESTS)
    set(project_test_name "${PROJECT_NAME}.tests")
    set(project_test_sources 
        tests/unit_tests.cpp
        tests/image_tests.cpp)
    add_executable(${project_test_name} ${project_test_sources})
    target_link_libraries(${project_test_name} 
        PUBLIC
            ${PROJECT_NAME}
            GTest::GTest
            GTest::Main
    )
    add_dependencies(${project_test_name} GTest::GTest GTest::Main)
endif(RAYRAY_BUILD_TESTS)
