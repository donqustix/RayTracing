#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "vector_types.h"

namespace osip
{
    struct Ray;
    struct Material;

    struct RenderObject
    {
        virtual ~RenderObject() = default;

        virtual bool intersect(Ray ray, float* t = nullptr,
                vec3f* intersectionPoint = nullptr) const noexcept = 0;

        virtual vec3f normal(const vec3f& point) const noexcept = 0;
        virtual vec3f color(const vec3f& point) const noexcept = 0;

        virtual Material getMaterial() const noexcept = 0;
    };
}

#endif
