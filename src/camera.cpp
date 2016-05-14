#include "camera.h"

#include <cassert>

using osip::Camera;
using osip::vec3f;

namespace osip
{
    struct Camera::Implementation
    {
        vec3f position;
        vec3f viewPoint;
        Basis basis;
        float fov;

        Implementation() noexcept :
            Implementation{{}, {0.0F, 0.0F, 1.0F}}
        {
        }

        Implementation(const vec3f& position, const vec3f& viewPoint, float fov = 60.0F) noexcept :
            position{position}, viewPoint{viewPoint}, basis(computeBasis()), fov{fov}
        {
            assert(fov > 0.0F);
        }

        Implementation(const Implementation& implementation) noexcept :
            position{implementation.position}, viewPoint{implementation.viewPoint},
            basis(implementation.basis), fov{implementation.fov}
        {
        }

        Basis computeBasis() const noexcept
        {
            const vec3f direction{viewPoint - position};
            const vec3f right{vec3f{0.0F, 1.0F, 0.0F}.cross(direction)};
            const vec3f up = right.cross(direction);

            return {direction, right, up};
        }
    };
}

Camera::Camera() :
    implementation{std::make_unique<Implementation>()}
{
}

Camera::Camera(const Camera& camera) :
    implementation{std::make_unique<Implementation>(*camera.implementation)}
{
}

Camera::Camera(Camera&&) noexcept = default;

Camera::~Camera() = default;

Camera& Camera::operator=(const Camera& camera)
{
    if (this == &camera)
        return *this;

    implementation.reset();
    implementation = std::make_unique<Implementation>(*camera.implementation);

    return *this;
}

Camera& Camera::operator=(Camera&&) noexcept = default;

const vec3f& Camera::getPosition() const noexcept
{
    return implementation->position;
}

const vec3f& Camera::getViewPoint() const noexcept
{
    return implementation->viewPoint;
}

Camera::Basis Camera::getBasis() const noexcept
{
    return implementation->basis;
}

float Camera::getFov() const noexcept
{
    return implementation->fov;
}

