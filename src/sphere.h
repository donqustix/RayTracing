#ifndef SPHERE_H
#define SPHERE_H

#include "render_object.h"

#include <memory>

namespace osip
{
    class Sphere : public RenderObject
    {
        struct Implementation;
        std::unique_ptr<Implementation> implementation;

    public:
        Sphere(const vec3f& position, const vec3f& color, float radius, Material material);
        Sphere(const Sphere& sphere);
        Sphere(Sphere&&) noexcept;
        ~Sphere();

        Sphere& operator=(const Sphere& sphere);
        Sphere& operator=(Sphere&&) noexcept;

        bool intersect(Ray ray, float* t = nullptr,
                vec3f* intersectionPoint = nullptr) const noexcept override;

        vec3f normal(const vec3f& point) const noexcept override;
        vec3f color(const vec3f& point) const noexcept override;

        Material getMaterial() const noexcept override;
    };
}

#endif
