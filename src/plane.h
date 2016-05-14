#ifndef PLANE_H
#define PLANE_H

#include "render_object.h"

#include <memory>

namespace osip
{
    class Plane : public RenderObject
    {
        struct Implementation;
        std::unique_ptr<Implementation> implementation;

    public:
        Plane(const vec3f& position, const vec3f& normal, const vec3f& color,
                Material material);

        Plane(const Plane& plane);
        Plane(Plane&&) noexcept;
        ~Plane();

        Plane& operator=(const Plane& plane);
        Plane& operator=(Plane&&) noexcept;

        bool intersect(Ray ray, float* t = nullptr,
                vec3f* intersectionPoint = nullptr) const noexcept override;

        vec3f normal(const vec3f& point) const noexcept override;
        vec3f color(const vec3f& point) const noexcept override;

        Material getMaterial() const noexcept override;
    };
}

#endif
