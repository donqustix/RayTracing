#include "sphere.h"
#include "vector.h"
#include "material.h"
#include "ray.h"

#include <cmath>
#include <algorithm>
#include <cassert>

using osip::Sphere;
using osip::vec3f;
using osip::Material;

namespace osip
{
    struct Sphere::Implementation
    {
        vec3f position;
        vec3f color;
        float radius;
        Material material;

        Implementation(const vec3f& position, const vec3f& color, float radius,
                Material material) noexcept :
            position{position}, color{color}, radius{radius}, material(material)
        {
            assert(radius > 0.0F);
        }

        Implementation(const Implementation& implementation) noexcept :
            position{implementation.position}, color{implementation.color},
            radius{implementation.radius}, material(implementation.material)
        {
        }
    };
}

Sphere::Sphere(const vec3f& position, const vec3f& color, float radius, Material material) :
    implementation{std::make_unique<Implementation>(position, color, radius, material)}
{
}

Sphere::Sphere(const Sphere& sphere) :
    implementation{std::make_unique<Implementation>(*sphere.implementation)}
{
}

Sphere::Sphere(Sphere&&) noexcept = default;

Sphere::~Sphere() = default;

Sphere& Sphere::operator=(const Sphere& sphere)
{
    if (this == &sphere)
        return *this;

    implementation.reset();
    implementation = std::make_unique<Implementation>(*sphere.implementation);

    return *this;
}

Sphere& Sphere::operator=(Sphere&&) noexcept = default;

bool Sphere::intersect(Ray ray, float* t, vec3f* intersectionPoint) const noexcept
{
    const vec3f k{implementation->position - ray.position};

    const float a = ray.direction.dot(k);
    const float D = a * a - (k.dot(k) - implementation->radius * implementation->radius);

    if (D < 0.0F)
        return false;

    const float sqrtD = std::sqrt(D);
    const float t1 = a - sqrtD;
    const float t2 = a + sqrtD;

    const float minT = std::min(t1, t2);
    const float maxT = std::max(t1, t2);

    const float fineT = minT >= 0.0F ? minT : maxT;

    if (fineT < 0.0F)
        return false;

    if (t) *t = fineT;

    if (intersectionPoint)
        *intersectionPoint = ray.position + ray.direction * fineT;

    return true;
}

vec3f Sphere::normal(const vec3f& point) const noexcept
{
    return (point - implementation->position).normalize();
}

vec3f Sphere::color(const vec3f& point) const noexcept
{
    return implementation->color;
}

Material Sphere::getMaterial() const noexcept
{
    return implementation->material;
}

