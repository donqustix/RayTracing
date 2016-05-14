#include "plane.h"
#include "vector.h"
#include "ray.h"
#include "material.h"

using osip::Plane;
using osip::vec3f;
using osip::Material;

namespace osip
{
    struct Plane::Implementation
    {
        vec3f position;
        vec3f normal;
        vec3f color;
        Material material;

        Implementation(const vec3f& position, const vec3f& normal, const vec3f& color,
                Material material) noexcept :
            position{position}, normal{normal}, color{color}, material(material)
        {
        }

        Implementation(const Implementation& implementation) noexcept :
            position{implementation.position}, normal{implementation.normal},
            color{implementation.color}, material(implementation.material)
        {
        }
    };
}

Plane::Plane(const vec3f& position, const vec3f& normal, const vec3f& color,
        Material material) :
    implementation{std::make_unique<Implementation>(position, normal, color, material)}
{
}

Plane::Plane(const Plane& plane) :
    implementation{std::make_unique<Implementation>(*plane.implementation)}
{
}

Plane::Plane(Plane&&) noexcept = default;

Plane::~Plane() = default;

Plane& Plane::operator=(const Plane& plane)
{
    if (this == &plane)
        return *this;

    implementation.reset();
    implementation = std::make_unique<Implementation>(*plane.implementation);

    return *this;
}

Plane& Plane::operator=(Plane&&) noexcept = default;

bool Plane::intersect(Ray ray, float* t, vec3f* intersectionPoint) const noexcept
{
    const float denom = ray.direction.dot(implementation->normal);
    if (denom < 1e-6F)
        return false;

    const float fineT = (implementation->position - ray.position).dot(implementation->normal) / denom;
    if (fineT < 0.0F)
        return false;

    if (t) *t = fineT;

    if (intersectionPoint)
        *intersectionPoint = ray.position + ray.direction * fineT;

    return true;
}

vec3f Plane::normal(const vec3f& point) const noexcept
{
    return -implementation->normal;
}

vec3f Plane::color(const vec3f& point) const noexcept
{
    return (int(point.getX()) + int(point.getY())) / 40 % 2 ? vec3f{1.0F, 1.0F, 1.0F} : implementation->color;
}

Material Plane::getMaterial() const noexcept
{
    return implementation->material;
}

